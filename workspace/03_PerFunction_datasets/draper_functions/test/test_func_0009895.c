autoUpdateLod(long x, long y, bool synchronous, const Any &data)
    {
        if(mAutoUpdateLod)
        {
            TerrainSlot* slot = getTerrainSlot(x, y, synchronous);
            if (slot)
            {
                mAutoUpdateLod->autoUpdateLod(slot->instance, synchronous, data);
            }
        }
    }
