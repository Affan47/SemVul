prepareTempBlendBuffers(void)
    {
        if (mSubMesh->useSharedVertices)
            return;

        if (mSkelAnimVertexData)
        {
            OGRE_DELETE mSkelAnimVertexData;
            mSkelAnimVertexData = 0;
        }
        if (mSoftwareVertexAnimVertexData)
        {
            OGRE_DELETE mSoftwareVertexAnimVertexData;
            mSoftwareVertexAnimVertexData = 0;
        }
        if (mHardwareVertexAnimVertexData)
        {
            OGRE_DELETE mHardwareVertexAnimVertexData;
            mHardwareVertexAnimVertexData = 0;
        }

        if (!mSubMesh->useSharedVertices)
        {
            if (mSubMesh->getVertexAnimationType() != VAT_NONE)
            {


                mSoftwareVertexAnimVertexData = mSubMesh->vertexData->clone(false);
                mParentEntity->extractTempBufferInfo(mSoftwareVertexAnimVertexData, &mTempVertexAnimInfo);


                mHardwareVertexAnimVertexData = mSubMesh->vertexData->clone(false);
            }

            if (mParentEntity->hasSkeleton())
            {


                mSkelAnimVertexData =
                    mParentEntity->cloneVertexDataRemoveBlendInfo(mSubMesh->vertexData);
                mParentEntity->extractTempBufferInfo(mSkelAnimVertexData, &mTempSkelAnimInfo);

            }
        }
    }
