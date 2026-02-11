getResourceGroups(void)
    {
            OGRE_LOCK_AUTO_MUTEX;
        StringVector vec;
        for (ResourceGroupMap::iterator i = mResourceGroupMap.begin();
            i != mResourceGroupMap.end(); ++i)
        {
            vec.push_back(i->second->name);
        }
        return vec;
    }
