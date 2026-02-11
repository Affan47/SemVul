readGeometryTexCoords(unsigned short bindIdx,
        DataStreamPtr& stream, Mesh* pMesh, VertexData* dest, unsigned short texCoordSet)
    {
        float *pFloat = 0;
        HardwareVertexBufferSharedPtr vbuf;

        unsigned short dim;
        readShorts(stream, &dim, 1);

        dest->vertexDeclaration->addElement(
            bindIdx,
            0,
            VertexElement::multiplyTypeCount(VET_FLOAT1, dim),
            VES_TEXTURE_COORDINATES,
            texCoordSet);
        vbuf = HardwareBufferManager::getSingleton().createVertexBuffer(
            dest->vertexDeclaration->getVertexSize(bindIdx),
            dest->vertexCount,
            pMesh->mVertexBufferUsage,
            pMesh->mVertexBufferShadowBuffer);
        pFloat = static_cast<float*>(
            vbuf->lock(HardwareBuffer::HBL_DISCARD));
        readFloats(stream, pFloat, dest->vertexCount * dim);
        vbuf->unlock();
        dest->vertexBufferBinding->setBinding(bindIdx, vbuf);
    }
