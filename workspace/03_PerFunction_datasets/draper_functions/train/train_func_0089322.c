calculateBounds(VertexData* vertexData,
        const Vector3& position, const Quaternion& orientation,
        const Vector3& scale)
    {
        const VertexElement* posElem =
            vertexData->vertexDeclaration->findElementBySemantic(
                VES_POSITION);
        HardwareVertexBufferSharedPtr vbuf =
            vertexData->vertexBufferBinding->getBuffer(posElem->getSource());
        unsigned char* vertex =
            static_cast<unsigned char*>(
                vbuf->lock(HardwareBuffer::HBL_READ_ONLY));
        float* pFloat;

        Vector3 min = Vector3::ZERO, max = Vector3::UNIT_SCALE;
        bool first = true;

        for(size_t j = 0; j < vertexData->vertexCount; ++j, vertex += vbuf->getVertexSize())
        {
            posElem->baseVertexPointerToElement(vertex, &pFloat);

            Vector3 pt;

            pt.x = (*pFloat++);
            pt.y = (*pFloat++);
            pt.z = (*pFloat++);

            pt = (orientation * (pt * scale)) + position;
            if (first)
            {
                min = max = pt;
                first = false;
            }
            else
            {
                min.makeFloor(pt);
                max.makeCeil(pt);
            }

        }
        vbuf->unlock();
        return AxisAlignedBox(min, max);
    }
