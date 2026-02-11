clone() const
        {
            std::string _cubeinput = "unknown";
                 if(m_cubeinput == TL_INPUT_LOG) _cubeinput = "log";
            else if(m_cubeinput == TL_INPUT_LIN) _cubeinput = "linear";
            else if(m_cubeinput == TL_INPUT_VID) _cubeinput = "video";
            OpRcPtr op = OpRcPtr(new TruelightOp(m_configroot.c_str(),
                                                 m_profile.c_str(),
                                                 m_camera.c_str(),
                                                 m_inputdisplay.c_str(),
                                                 m_recorder.c_str(),
                                                 m_print.c_str(),
                                                 m_lamp.c_str(),
                                                 m_outputcamera.c_str(),
                                                 m_display.c_str(),
                                                 _cubeinput.c_str(),
                                                 m_direction));
            return op;
        }
