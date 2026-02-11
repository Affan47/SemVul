addRequest(uint16 channel, uint16 requestType,
        const Any& rData, uint8 retryCount, bool forceSynchronous, bool idleThread)
    {
        Request* req = 0;
        RequestID rid = 0;

        {

                    OGRE_LOCK_MUTEX(mRequestMutex);

            if (!mAcceptRequests || mShuttingDown)
                return 0;

            rid = ++mRequestCount;
            req = OGRE_NEW Request(channel, requestType, rData, retryCount, rid);

            LogManager::getSingleton().stream(LML_TRIVIAL) <<
                "DefaultWorkQueueBase('" << mName << "') - QUEUED(thread:" <<
#if OGRE_THREAD_SUPPORT
                OGRE_THREAD_CURRENT_ID
#else
                "main"
#endif
                << "): ID=" << rid
                << " channel=" << channel << " requestType=" << requestType;
#if OGRE_THREAD_SUPPORT
            if (!forceSynchronous&& !idleThread)
            {
                mRequestQueue.push_back(req);
                notifyWorkers();
                return rid;
            }
#endif
        }
        if(OGRE_THREAD_SUPPORT && idleThread){
            OGRE_LOCK_MUTEX(mIdleMutex);
            mIdleRequestQueue.push_back(req);
            if(!mIdleThreadRunning)
            {
                notifyWorkers();
            }
        } else {
            processRequestResponse(req, true);
        }
        return rid;

    }
