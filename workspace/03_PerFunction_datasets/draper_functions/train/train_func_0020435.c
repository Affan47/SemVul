unload(
        const String& resType, ResourceHandle handle, Listener* listener)
    {
#if OGRE_THREAD_SUPPORT

        ResourceRequest req;
        req.type = RT_UNLOAD_RESOURCE;
        req.resourceType = resType;
        req.resourceHandle = handle;
        req.listener = listener;
        return addRequest(req);
#else

        ResourceManager* rm =
            ResourceGroupManager::getSingleton()._getResourceManager(resType);
        rm->unload(handle);
        return 0;
#endif

    }
