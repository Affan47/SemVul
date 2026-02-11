calcGeometrySize(const VertexData* vertexData)
    {
        const VertexDeclaration::VertexElementList& elemList =
            vertexData->vertexDeclaration->getElements();
        const VertexBufferBinding::VertexBufferBindingMap& bindings =
            vertexData->vertexBufferBinding->getBindings();
        size_t size = MSTREAM_OVERHEAD_SIZE;


        size += sizeof(unsigned int);


        size += MSTREAM_OVERHEAD_SIZE + elemList.size() * (MSTREAM_OVERHEAD_SIZE + sizeof(unsigned short)* 5);


        size += bindings.size() * ((MSTREAM_OVERHEAD_SIZE * 2) + (sizeof(unsigned short)* 2));


        VertexBufferBinding::VertexBufferBindingMap::const_iterator vbi, vbiend;
        vbiend = bindings.end();
        for (vbi = bindings.begin(); vbi != vbiend; ++vbi)
        {
            const HardwareVertexBufferSharedPtr& vbuf = vbi->second;
            size += vbuf->getSizeInBytes();
        }
        return size;
    }
