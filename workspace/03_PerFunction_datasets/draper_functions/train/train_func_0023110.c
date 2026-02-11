extendBuffers(VertexSplits& vertexSplits)
    {
        if (!vertexSplits.empty())
        {


            VertexBufferBinding* newBindings = HardwareBufferManager::getSingleton().createVertexBufferBinding();
            const VertexBufferBinding::VertexBufferBindingMap& bindmap =
                mVData->vertexBufferBinding->getBindings();
            for (VertexBufferBinding::VertexBufferBindingMap::const_iterator i =
                bindmap.begin(); i != bindmap.end(); ++i)
            {
                HardwareVertexBufferSharedPtr srcbuf = i->second;


                size_t newVertexCount = srcbuf->getNumVertices() + vertexSplits.size();

                HardwareVertexBufferSharedPtr newBuf =
                    HardwareBufferManager::getSingleton().createVertexBuffer(
                    srcbuf->getVertexSize(), newVertexCount, srcbuf->getUsage(),
                    srcbuf->hasShadowBuffer());
                newBindings->setBinding(i->first, newBuf);


                newBuf->copyData(*(srcbuf.get()), 0, 0, srcbuf->getNumVertices() * srcbuf->getVertexSize(), true);


                char* pBase = static_cast<char*>(newBuf->lock(HardwareBuffer::HBL_NORMAL));
                for (VertexSplits::iterator spliti = vertexSplits.begin();
                    spliti != vertexSplits.end(); ++spliti)
                {
                    const char* pSrcBase = pBase + spliti->first * newBuf->getVertexSize();
                    char* pDstBase = pBase + spliti->second * newBuf->getVertexSize();
                    memcpy(pDstBase, pSrcBase, newBuf->getVertexSize());
                }
                newBuf->unlock();

            }


            mVData->vertexCount += vertexSplits.size();

            HardwareBufferManager::getSingleton().destroyVertexBufferBinding(mVData->vertexBufferBinding);
            mVData->vertexBufferBinding = newBindings;


            if (mVData->vertexCount > 65536)
            {
                for (size_t i = 0; i < mIDataList.size(); ++i)
                {

                    IndexData* idata = mIDataList[i];
                    HardwareIndexBufferSharedPtr srcbuf = idata->indexBuffer;
                    if (srcbuf->getType() == HardwareIndexBuffer::IT_16BIT)
                    {
                        size_t indexCount = srcbuf->getNumIndexes();


                        HardwareIndexBufferSharedPtr newBuf =
                            HardwareBufferManager::getSingleton().createIndexBuffer(
                            HardwareIndexBuffer::IT_32BIT, indexCount,
                            srcbuf->getUsage(), srcbuf->hasShadowBuffer());

                        uint16* pSrcBase = static_cast<uint16*>(srcbuf->lock(HardwareBuffer::HBL_NORMAL));
                        uint32* pBase = static_cast<uint32*>(newBuf->lock(HardwareBuffer::HBL_NORMAL));

                        size_t j = 0;
                        while (j < indexCount)
                        {
                            *pBase++ = *pSrcBase++;
                            ++j;
                        }

                        srcbuf->unlock();
                        newBuf->unlock();


                        idata->indexBuffer = newBuf;
                    }
                }
            }
        }

    }
