getGeoDataSizeAtLod(uint16 lodLevel) const
    {
        uint size = getResolutionAtLod(lodLevel);
        uint prevSize = (lodLevel<mNumLodLevels-1) ? getResolutionAtLod(lodLevel+1) : 0;
        return size*size - prevSize*prevSize;
    }
