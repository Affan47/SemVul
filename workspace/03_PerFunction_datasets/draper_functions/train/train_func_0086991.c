_renderScene(Viewport *vp, bool includeOverlays)
    {
        OgreProfileBeginGPUEvent("Camera: " + getName());


        if (mProjType == Ogre::PT_PERSPECTIVE)
        {
            mPixelDisplayRatio = (2 * Ogre::Math::Tan(mFOVy * 0.5f)) / vp->getActualHeight();
        }
        else
        {
            mPixelDisplayRatio = (mTop - mBottom) / vp->getActualHeight();
        }


        ListenerList listenersCopy = mListeners;
        for (ListenerList::iterator i = listenersCopy.begin(); i != listenersCopy.end(); ++i)
        {
            (*i)->cameraPreRenderScene(this);
        }


        mSceneMgr->_renderScene(this, vp, includeOverlays);


        listenersCopy = mListeners;


        for (ListenerList::iterator i = listenersCopy.begin(); i != listenersCopy.end(); ++i)
        {
            (*i)->cameraPostRenderScene(this);
        }
        OgreProfileEndGPUEvent("Camera: " + getName());
    }
