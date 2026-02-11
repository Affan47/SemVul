setupIndices( const SubMesh* baseSubMesh )
    {
        mRenderOperation.indexData = OGRE_NEW IndexData();
        mRemoveOwnIndexData = true;

        IndexData *thisIndexData = mRenderOperation.indexData;
        IndexData *baseIndexData = baseSubMesh->indexData;

        thisIndexData->indexStart = 0;
        thisIndexData->indexCount = baseIndexData->indexCount * mInstancesPerBatch;


        HardwareIndexBuffer::IndexType indexType = HardwareIndexBuffer::IT_16BIT;
        if( mRenderOperation.vertexData->vertexCount > 65535 )
            indexType = HardwareIndexBuffer::IT_32BIT;
        thisIndexData->indexBuffer = HardwareBufferManager::getSingleton().createIndexBuffer(
                                                    indexType, thisIndexData->indexCount,
                                                    HardwareBuffer::HBU_STATIC_WRITE_ONLY );

        void *buf           = thisIndexData->indexBuffer->lock( HardwareBuffer::HBL_DISCARD );
        void const *baseBuf = baseIndexData->indexBuffer->lock( HardwareBuffer::HBL_READ_ONLY );

        uint16 *thisBuf16 = static_cast<uint16*>(buf);
        uint32 *thisBuf32 = static_cast<uint32*>(buf);

        for( size_t i=0; i<mInstancesPerBatch; ++i )
        {
            const size_t vertexOffset = i * mRenderOperation.vertexData->vertexCount / mInstancesPerBatch;

            uint16 const *initBuf16 = static_cast<uint16 const *>(baseBuf);
            uint32 const *initBuf32 = static_cast<uint32 const *>(baseBuf);

            for( size_t j=0; j<baseIndexData->indexCount; ++j )
            {
                uint32 originalVal;
                if( baseSubMesh->indexData->indexBuffer->getType() == HardwareIndexBuffer::IT_16BIT )
                    originalVal = *initBuf16++;
                else
                    originalVal = *initBuf32++;

                if( indexType == HardwareIndexBuffer::IT_16BIT )
                    *thisBuf16++ = static_cast<uint16>(originalVal) + vertexOffset;
                else
                    *thisBuf32++ = static_cast<uint32>(originalVal + vertexOffset);
            }
        }

        baseIndexData->indexBuffer->unlock();
        thisIndexData->indexBuffer->unlock();
    }
