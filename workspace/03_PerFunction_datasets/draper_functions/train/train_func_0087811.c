rebindPositionBuffer(const VertexData* vertexData, bool force)
    {
        if (force || mCurrentVertexData != vertexData)
        {
            mCurrentVertexData = vertexData;
            mPositionBuffer = mCurrentVertexData->vertexBufferBinding->getBuffer(
                mOriginalPosBufferBinding);
            mRenderOp.vertexData->vertexBufferBinding->setBinding(0, mPositionBuffer);
            if (mLightCap)
            {
                static_cast<EntityShadowRenderable*>(mLightCap)->rebindPositionBuffer(vertexData, force);
            }
        }
    }
