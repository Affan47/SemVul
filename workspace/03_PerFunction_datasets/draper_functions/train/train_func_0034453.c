unload(
        const String& resType, const String& name, Listener* listener)
    {
#if OGRE_THREAD_SUPPORT

        ResourceRequest req;
        req.type = RT_UNLOAD_RESOURCE;
        req.resourceType = resType;
        req.resourceName = name;
        req.listener = listener;
        return addRequest(req);
#else

        ResourceManager* rm =
            ResourceGroupManager::getSingleton()._getResourceManager(resType);
        rm->unload(name);
        return 0;
#endif

    }
