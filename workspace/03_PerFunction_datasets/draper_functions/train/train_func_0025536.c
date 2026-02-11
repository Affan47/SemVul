processSignal(cxxtools::IODevice& device)
    {
        try
        {
            size_t n = device.endRead();

            int sigNo = 0;
            char* it = _signalBuffer;
            char* last = &_signalBuffer[ n- sizeof(sigNo) ];
            while(it <= last)
            {
                memcpy(&sigNo, it, sizeof(sigNo));
                cxxtools::Application::instance().systemSignal.send(sigNo);
                it += sizeof(sigNo);
            }

            device.beginRead( _signalBuffer, sizeof(_signalBuffer) );
        }
        catch(...)
        {
            device.beginRead( _signalBuffer, sizeof(_signalBuffer) );
            throw;
        }
    }
