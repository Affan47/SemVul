loadImpl(void)
    {
        SubMesh* sm = this->createSubMesh();
        sm->vertexData = OGRE_NEW VertexData();
        sm->useSharedVertices = false;


        sm->vertexData->vertexStart = 0;
        sm->vertexData->vertexCount = mSurface.getRequiredVertexCount();
        sm->vertexData->vertexDeclaration = mDeclaration;
        HardwareVertexBufferSharedPtr vbuf = HardwareBufferManager::getSingleton().
            createVertexBuffer(
                mDeclaration->getVertexSize(0),
                sm->vertexData->vertexCount,
                mVertexBufferUsage,
                mVertexBufferShadowBuffer);
        sm->vertexData->vertexBufferBinding->setBinding(0, vbuf);


        sm->indexData->indexStart = 0;
        sm->indexData->indexCount = mSurface.getRequiredIndexCount();
        sm->indexData->indexBuffer = HardwareBufferManager::getSingleton().
            createIndexBuffer(
                HardwareIndexBuffer::IT_16BIT,
                sm->indexData->indexCount,
                mIndexBufferUsage,
                mIndexBufferShadowBuffer);


        mSurface.build(vbuf, 0, sm->indexData->indexBuffer, 0);


        this->_setBounds(mSurface.getBounds(), true);
        this->_setBoundingSphereRadius(mSurface.getBoundingSphereRadius());

    }
