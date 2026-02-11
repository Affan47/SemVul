install()
    {

        mPCZSMFactory = OGRE_NEW PCZSceneManagerFactory();
        mPCZoneFactoryManager = OGRE_NEW PCZoneFactoryManager();
        mPCZLightFactory = OGRE_NEW PCZLightFactory();
        mPortalFactory = OGRE_NEW PortalFactory();
        mAntiPortalFactory = OGRE_NEW AntiPortalFactory();
    }
