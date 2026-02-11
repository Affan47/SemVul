getVertexDataByTrackHandle(unsigned short handle)
    {
        if (handle == 0)
        {
            return sharedVertexData;
        }
        else
        {
            return getSubMesh(handle-1)->vertexData;
        }
    }
