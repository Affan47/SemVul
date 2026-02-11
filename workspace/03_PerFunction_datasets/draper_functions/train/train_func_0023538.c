writePose(const Pose* pose)
    {
        writeChunkHeader(M_POSE, calcPoseSize(pose));


        writeString(pose->getName());


        ushort val = pose->getTarget();
        writeShorts(&val, 1);


        bool includesNormals = !pose->getNormals().empty();
        writeBools(&includesNormals, 1);
        pushInnerChunk(mStream);
        {
            size_t vertexSize = calcPoseVertexSize(pose);
            Pose::ConstVertexOffsetIterator vit = pose->getVertexOffsetIterator();
            Pose::ConstNormalsIterator nit = pose->getNormalsIterator();
            while (vit.hasMoreElements())
            {
                uint32 vertexIndex = (uint32)vit.peekNextKey();
                Vector3 offset = vit.getNext();
                writeChunkHeader(M_POSE_VERTEX, vertexSize);

                writeInts(&vertexIndex, 1);

                writeFloats(offset.ptr(), 3);
                if (includesNormals)
                {
                    Vector3 normal = nit.getNext();

                    writeFloats(normal.ptr(), 3);
                }
            }
        }
        popInnerChunk(mStream);
    }
