setVSyncInterval(unsigned int interval)
    {
        mVSyncInterval = interval;
        if (mVSync)
            setVSyncEnabled(true);
    }
