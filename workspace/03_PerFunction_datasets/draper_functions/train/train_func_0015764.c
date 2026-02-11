_switchContext(GLContext *context)
    {


        if (mCurrentVertexProgram)
            mCurrentVertexProgram->unbindProgram();
        if (mCurrentGeometryProgram)
            mCurrentGeometryProgram->unbindProgram();
        if (mCurrentFragmentProgram)
            mCurrentFragmentProgram->unbindProgram();


        for (unsigned short i = 0; i < mCurrentLights; ++i)
        {
            setGLLight(i, NULL);
            mLights[i] = NULL;
        }
        mCurrentLights = 0;


        _disableTextureUnitsFrom(0);


        if (mCurrentContext)
            mCurrentContext->endCurrent();
        mCurrentContext = context;
        mCurrentContext->setCurrent();

        mStateCacheManager->switchContext((intptr_t)mCurrentContext);


        if(!mCurrentContext->getInitialized())
        {
            _oneTimeContextInitialization();
            mCurrentContext->setInitialized();
        }


        if (mCurrentVertexProgram)
            mCurrentVertexProgram->bindProgram();
        if (mCurrentGeometryProgram)
            mCurrentGeometryProgram->bindProgram();
        if (mCurrentFragmentProgram)
            mCurrentFragmentProgram->bindProgram();


        mStateCacheManager->setDepthMask(mDepthWrite);
        mStateCacheManager->setColourMask(mColourWrite[0], mColourWrite[1], mColourWrite[2], mColourWrite[3]);
        mStateCacheManager->setStencilMask(mStencilWriteMask);

    }
