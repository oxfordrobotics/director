#ifndef __ddROSInit_h
#define __ddROSInit_h

#include <QObject>
#include <ddMacros.h>
#include <PythonQt.h>

#include <ros/ros.h>

#include "ddAppConfigure.h"

class DD_APP_EXPORT ddROSInit : public QObject {
    Q_OBJECT
public:
    static void initialiseROS(const QList<QString>& argv2)
    {
        if (!ros::isInitialized()) {
            // guarantee contiguous, null terminated strings
            std::vector<std::vector<char>> vstrings;
            // pointers to rhose strings
            std::vector<char*> cstrings;
            vstrings.reserve(argv2.size());
            cstrings.reserve(argv2.size());

            for(size_t i = 0; i < argv2.size(); ++i) {
                std::string argv_string = argv2[i].toStdString();
                vstrings.emplace_back(argv_string.begin(), argv_string.end());
                vstrings.back().push_back('\0');
                cstrings.push_back(vstrings.back().data());
            }
            int argc = cstrings.size();

            ros::init(argc, cstrings.data(), "director_dd", ros::init_options::NoSigintHandler |
                        ros::init_options::AnonymousName);
        }
    }
};

#endif    