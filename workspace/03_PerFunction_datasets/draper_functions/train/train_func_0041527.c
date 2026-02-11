destroyCpuVertexData()
    {
        if (mVertexDataRecord && mVertexDataRecord->cpuVertexData)
        {

            mVertexDataRecord->gpuVertexDataDirty = false;

            OGRE_DELETE mVertexDataRecord->cpuVertexData->vertexDeclaration;
            mVertexDataRecord->cpuVertexData->vertexDeclaration = 0;

            OGRE_DELETE mVertexDataRecord->cpuVertexData->vertexBufferBinding;
            mVertexDataRecord->cpuVertexData->vertexBufferBinding = 0;

            OGRE_DELETE mVertexDataRecord->cpuVertexData;
            mVertexDataRecord->cpuVertexData = 0;
        }


    }
