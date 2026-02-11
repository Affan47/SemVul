queueForDeletion(void)
    {
        mQueuedForDeletion = true;

        removeAllTextureUnitStates();
        if (mVertexProgramUsage)
        {
            OGRE_DELETE mVertexProgramUsage;
            mVertexProgramUsage = 0;
        }
        if (mShadowCasterVertexProgramUsage)
        {
            OGRE_DELETE mShadowCasterVertexProgramUsage;
            mShadowCasterVertexProgramUsage = 0;
        }
        if (mShadowCasterFragmentProgramUsage)
        {
            OGRE_DELETE mShadowCasterFragmentProgramUsage;
            mShadowCasterFragmentProgramUsage = 0;
        }
        if (mShadowReceiverVertexProgramUsage)
        {
            OGRE_DELETE mShadowReceiverVertexProgramUsage;
            mShadowReceiverVertexProgramUsage = 0;
        }
        if (mGeometryProgramUsage)
        {
            delete mGeometryProgramUsage;
            mGeometryProgramUsage = 0;
        }
        if (mFragmentProgramUsage)
        {
            OGRE_DELETE mFragmentProgramUsage;
            mFragmentProgramUsage = 0;
        }
        if (mTessellationHullProgramUsage)
        {
            OGRE_DELETE mTessellationHullProgramUsage;
            mTessellationHullProgramUsage = 0;
        }
        if (mTessellationDomainProgramUsage)
        {
            OGRE_DELETE mTessellationDomainProgramUsage;
            mTessellationDomainProgramUsage = 0;
        }
        if (mComputeProgramUsage)
        {
            OGRE_DELETE mComputeProgramUsage;
            mComputeProgramUsage = 0;
        }
        if (mShadowReceiverFragmentProgramUsage)
        {
            OGRE_DELETE mShadowReceiverFragmentProgramUsage;
            mShadowReceiverFragmentProgramUsage = 0;
        }

        {
                    OGRE_LOCK_MUTEX(msDirtyHashListMutex);
            msDirtyHashList.erase(this);
        }
        {
                    OGRE_LOCK_MUTEX(msPassGraveyardMutex);
            msPassGraveyard.insert(this);
        }
    }
