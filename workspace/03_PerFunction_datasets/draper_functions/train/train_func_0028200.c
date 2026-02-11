install()
    {
        mRenderSystem = OGRE_NEW GLRenderSystem();

        Root::getSingleton().addRenderSystem(mRenderSystem);
    }
