initialise()
    {

        Root::getSingleton().addSceneManagerFactory(mBspFactory);

        mBspResourceManager = OGRE_NEW BspResourceManager();
    }
