populateIndexData(uint16 batchSize, IndexData* destData)
    {
        const VertexDataRecord* vdr = getVertexDataRecord();


        size_t resolutionRatio = (mTerrain->getSize() - 1) / (vdr->resolution - 1);


        size_t vertexIncrement = (mSize-1) / (batchSize-1);

        vertexIncrement /= resolutionRatio;
        uint16 vdatasizeOffsetX = (mOffsetX - mNodeWithVertexData->mOffsetX) / resolutionRatio;
        uint16 vdatasizeOffsetY = (mOffsetY - mNodeWithVertexData->mOffsetY) / resolutionRatio;

        destData->indexBuffer = mTerrain->getGpuBufferAllocator()->getSharedIndexBuffer(batchSize, vdr->size,
            vertexIncrement, vdatasizeOffsetX, vdatasizeOffsetY,
            vdr->numSkirtRowsCols, vdr->skirtRowColSkip);
        destData->indexStart = 0;
        destData->indexCount = destData->indexBuffer->getNumIndexes();


    }
