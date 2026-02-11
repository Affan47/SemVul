setCamera(Camera* cam)
    {
        if (cam != NULL && mCamera != NULL && mCamera->getViewport() == this)
        {
                mCamera->_notifyViewport(NULL);
        }

        mCamera = cam;
        if (cam)
        {

            if (cam->getAutoAspectRatio())
            {
                cam->setAspectRatio((Real) mActWidth / (Real) mActHeight);
            }
#if OGRE_NO_VIEWPORT_ORIENTATIONMODE == 0
            cam->setOrientationMode(mOrientationMode);
#endif
            cam->_notifyViewport(this);
        }

        for (ListenerList::iterator i = mListeners.begin(); i != mListeners.end(); ++i)
        {
            (*i)->viewportCameraChanged(this);
        }
    }
