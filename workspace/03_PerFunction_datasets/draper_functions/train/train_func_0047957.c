_freeUnusedBufferCopies(void)
    {
        OGRE_LOCK_MUTEX(mTempBuffersMutex);
        size_t numFreed = 0;


        FreeTemporaryVertexBufferMap::iterator i;
        i = mFreeTempVertexBufferMap.begin();
        while (i != mFreeTempVertexBufferMap.end())
        {
            FreeTemporaryVertexBufferMap::iterator icur = i++;


            if (icur->second.useCount() <= 1)
            {
                ++numFreed;
                mFreeTempVertexBufferMap.erase(icur);
            }
        }

        StringStream str;
        if (numFreed)
        {
            str << "HardwareBufferManager: Freed " << numFreed << " unused temporary vertex buffers.";
        }
        else
        {
            str << "HardwareBufferManager: No unused temporary vertex buffers found.";
        }
        LogManager::getSingleton().logMessage(str.str(), LML_TRIVIAL);
    }
