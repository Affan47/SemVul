addCreatedResource(ResourcePtr& res, ResourceGroup& grp)
    {
            OGRE_LOCK_MUTEX(grp.OGRE_AUTO_MUTEX_NAME);
        Real order = res->getCreator()->getLoadingOrder();

        ResourceGroup::LoadResourceOrderMap::iterator i = grp.loadResourceOrderMap.find(order);
        LoadUnloadResourceList* loadList;
        if (i == grp.loadResourceOrderMap.end())
        {
            loadList = OGRE_NEW_T(LoadUnloadResourceList, MEMCATEGORY_RESOURCE)();
            grp.loadResourceOrderMap[order] = loadList;
        }
        else
        {
            loadList = i->second;
        }
        loadList->push_back(res);
    }
