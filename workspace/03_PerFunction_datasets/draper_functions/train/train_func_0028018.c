getDebugRenderable(Real scaling)
    {
        if (!mDebug)
        {
            mDebug = OGRE_NEW DebugRenderable(this);
        }
        mDebug->setScaling(scaling);
        return mDebug;
    }
