fillBufferAtLod(uint lodLevel, const float* data, uint dataSize )
    {
        unsigned int inc = 1 << lodLevel;
        unsigned int prev = 1 << (lodLevel + 1);
        uint16 numLodLevels = mTerrain->getNumLodLevels();
        uint16 size = mTerrain->getSize();

        const float* heightDataPtr = data;
        const float* deltaDataPtr = data+dataSize/2;

        for (uint16 y = 0; y < size; y += inc)
        {
            for (uint16 x = 0; x < size-1; x += inc)
                if ((lodLevel == numLodLevels - static_cast<uint>(1)) || (x % prev) || (y % prev))
                {
                    mTerrain->mHeightData[y*size + x] = *(heightDataPtr++);
                    mTerrain->mDeltaData[y*size + x] = *(deltaDataPtr++);
                }
            if ((lodLevel == numLodLevels - static_cast<uint>(1)) || (y % prev))
            {
                mTerrain->mHeightData[y*size + size-1] = *(heightDataPtr++);
                mTerrain->mDeltaData[y*size + size-1] = *(deltaDataPtr++);
            }
            if (y+inc > size)
                break;
        }
    }
