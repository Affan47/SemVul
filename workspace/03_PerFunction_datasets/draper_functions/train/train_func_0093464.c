_destroyBuffers(void)
    {
        if (mVertexData)
        {
            OGRE_DELETE mVertexData;
            mVertexData = 0;
        }
        if (mIndexData)
        {
            OGRE_DELETE mIndexData;
            mIndexData = 0;
        }

        mMainBuf.setNull();

        mBuffersCreated = false;

    }
