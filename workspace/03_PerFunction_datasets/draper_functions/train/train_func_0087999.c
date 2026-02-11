setTerrainSize(uint16 newTerrainSize)
    {
        if (newTerrainSize != mTerrainSize)
        {
            mTerrainSize = newTerrainSize;
            for (TerrainSlotMap::iterator i = mTerrainSlots.begin(); i != mTerrainSlots.end(); ++i)
            {
                if (i->second->instance)
                {
                    i->second->instance->setSize(newTerrainSize);
                }
            }
        }
    }
