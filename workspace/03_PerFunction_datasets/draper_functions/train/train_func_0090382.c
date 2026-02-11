setupVertices( const SubMesh* baseSubMesh )
    {
        mRenderOperation.vertexData = OGRE_NEW VertexData();
        mRemoveOwnVertexData = true;

        VertexData *thisVertexData = mRenderOperation.vertexData;
        VertexData *baseVertexData = baseSubMesh->vertexData;

        thisVertexData->vertexStart = 0;
        thisVertexData->vertexCount = baseVertexData->vertexCount * mInstancesPerBatch;

        HardwareBufferManager::getSingleton().destroyVertexDeclaration( thisVertexData->vertexDeclaration );
        thisVertexData->vertexDeclaration = baseVertexData->vertexDeclaration->clone();

        if( mMeshReference->hasSkeleton() && !mMeshReference->getSkeleton().isNull() )
        {

            setupHardwareSkinned( baseSubMesh, thisVertexData, baseVertexData );
            return;
        }


        thisVertexData->vertexDeclaration->addElement(
                                        thisVertexData->vertexDeclaration->getMaxSource() + 1, 0,
                                        VET_UBYTE4, VES_BLEND_INDICES );


        for( uint16 i=0; i<thisVertexData->vertexDeclaration->getMaxSource(); ++i )
        {

            HardwareVertexBufferSharedPtr vertexBuffer =
                                            HardwareBufferManager::getSingleton().createVertexBuffer(
                                            thisVertexData->vertexDeclaration->getVertexSize(i),
                                            thisVertexData->vertexCount,
                                            HardwareBuffer::HBU_STATIC_WRITE_ONLY );
            thisVertexData->vertexBufferBinding->setBinding( i, vertexBuffer );


            HardwareVertexBufferSharedPtr baseVertexBuffer =
                                                    baseVertexData->vertexBufferBinding->getBuffer(i);

            char* thisBuf = static_cast<char*>(vertexBuffer->lock(HardwareBuffer::HBL_DISCARD));
            char* baseBuf = static_cast<char*>(baseVertexBuffer->lock(HardwareBuffer::HBL_READ_ONLY));


            for( size_t j=0; j<mInstancesPerBatch; ++j )
            {
                const size_t sizeOfBuffer = baseVertexData->vertexCount *
                                            baseVertexData->vertexDeclaration->getVertexSize(i);
                memcpy( thisBuf + j * sizeOfBuffer, baseBuf, sizeOfBuffer );
            }

            baseVertexBuffer->unlock();
            vertexBuffer->unlock();
        }

        {

            const unsigned short lastSource = thisVertexData->vertexDeclaration->getMaxSource();
            HardwareVertexBufferSharedPtr vertexBuffer =
                                            HardwareBufferManager::getSingleton().createVertexBuffer(
                                            thisVertexData->vertexDeclaration->getVertexSize( lastSource ),
                                            thisVertexData->vertexCount,
                                            HardwareBuffer::HBU_STATIC_WRITE_ONLY );
            thisVertexData->vertexBufferBinding->setBinding( lastSource, vertexBuffer );

            char* thisBuf = static_cast<char*>(vertexBuffer->lock(HardwareBuffer::HBL_DISCARD));
            for( size_t j=0; j<mInstancesPerBatch; ++j )
            {
                for( size_t k=0; k<baseVertexData->vertexCount; ++k )
                {
                    *thisBuf++ = j;
                    *thisBuf++ = j;
                    *thisBuf++ = j;
                    *thisBuf++ = j;
                }
            }

            vertexBuffer->unlock();
        }
    }
