_restoreManualHardwareResources()
    {
        if(!mInitialised)
            return;

        VertexDeclaration* decl = mRenderOp.vertexData->vertexDeclaration;


        HardwareVertexBufferSharedPtr vbuf =
            HardwareBufferManager::getSingleton().createVertexBuffer(
            decl->getVertexSize(POSITION_BINDING), mRenderOp.vertexData->vertexCount,
            HardwareBuffer::HBU_STATIC_WRITE_ONLY
            );

        mRenderOp.vertexData->vertexBufferBinding->setBinding(POSITION_BINDING, vbuf);


        mGeomPositionsOutOfDate = true;
        mGeomUVsOutOfDate = true;
    }
