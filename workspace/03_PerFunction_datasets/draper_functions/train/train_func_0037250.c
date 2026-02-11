terminate()
    {
        XmpProperties::unregisterNs();
        if (initialized_) {
#ifdef EXV_HAVE_XMP_TOOLKIT
            SXMPMeta::Terminate();
#endif
            xmpLockFct_ = 0;
            pLockData_ = 0;
            initialized_ = false;
        }
    }
