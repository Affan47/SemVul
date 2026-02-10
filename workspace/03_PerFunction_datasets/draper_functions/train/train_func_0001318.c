assign(QueuedGeometry* qgeom)
    {

        if (mRenderOp.vertexData->vertexCount + qgeom->geometry->vertexData->vertexCount
            > mMaxVertexIndex)
        {
            return false;
        }

        mQueuedGeometry.push_back(qgeom);
        mRenderOp.vertexData->vertexCount += qgeom->geometry->vertexData->vertexCount;
        mRenderOp.indexData->indexCount += qgeom->geometry->indexData->indexCount;

        return true;
    }
