removeVertex(size_t index)
    {
        VertexOffsetMap::iterator i = mVertexOffsetMap.find(index);
        if (i != mVertexOffsetMap.end())
        {
            mVertexOffsetMap.erase(i);
            mBuffer.setNull();
        }
        NormalsMap::iterator j = mNormalsMap.find(index);
        if (j != mNormalsMap.end())
        {
            mNormalsMap.erase(j);
        }
    }
