unregisterContext(intptr_t id)
    {
        CachesMap::iterator it = mCaches.find(id);
        if (it != mCaches.end())
        {
            if (mImp == it->second)
                mImp = NULL;
            OGRE_DELETE it->second;
            mCaches.erase(it);
        }


        if (mImp == NULL)
        {

            if (mCaches.empty())
                mCaches[0] = OGRE_NEW GLStateCacheManagerImp();
            mImp = mCaches.begin()->second;
        }
    }
