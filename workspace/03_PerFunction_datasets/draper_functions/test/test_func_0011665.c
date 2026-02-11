LoadMapTile(uint32 tileX, uint32 tileY, VMapManager2* vm)
    {
        if (!iIsTiled)
        {


            iLoadedTiles[packTileID(tileX, tileY)] = false;
            return true;
        }
        if (!iTreeValues)
        {
            ERROR_LOG("StaticMapTree::LoadMapTile(): Tree has not been initialized! [%u,%u]", tileX, tileY);
            return false;
        }
        bool result = true;

        std::string tilefile = iBasePath + getTileFileName(iMapID, tileX, tileY);
        FILE* tf = fopen(tilefile.c_str(), "rb");
        if (tf)
        {
            char chunk[8];
            if (!readChunk(tf, chunk, VMAP_MAGIC, 8))
                { result = false; }
            uint32 numSpawns = 0;
            if (result && fread(&numSpawns, sizeof(uint32), 1, tf) != 1)
                { result = false; }
            for (uint32 i = 0; i < numSpawns && result; ++i)
            {

                ModelSpawn spawn;
                result = ModelSpawn::readFromFile(tf, spawn);
                if (result)
                {

                    WorldModel* model = vm->acquireModelInstance(iBasePath, spawn.name);
                    if (!model)
                        { ERROR_LOG("StaticMapTree::LoadMapTile() could not acquire WorldModel pointer for '%s'!", spawn.name.c_str()); }


                    uint32 referencedVal;

                    size_t fileRead = fread(&referencedVal, sizeof(uint32), 1, tf);
                    if (!iLoadedSpawns.count(referencedVal) || fileRead <= 0)
                    {
#ifdef VMAP_DEBUG
                        if (referencedVal > iNTreeValues)
                        {
                            DEBUG_LOG("invalid tree element! (%u/%u)", referencedVal, iNTreeValues);
                            continue;
                        }
#endif
                        iTreeValues[referencedVal] = ModelInstance(spawn, model);
                        iLoadedSpawns[referencedVal] = 1;
                    }
                    else
                    {
                        ++iLoadedSpawns[referencedVal];
#ifdef VMAP_DEBUG
                        if (iTreeValues[referencedVal].ID != spawn.ID)
                            { DEBUG_LOG("Error: trying to load wrong spawn in node!"); }
                        else if (iTreeValues[referencedVal].name != spawn.name)
                            { DEBUG_LOG("Error: name mismatch on GUID=%u", spawn.ID); }
#endif
                    }
                }
            }
            iLoadedTiles[packTileID(tileX, tileY)] = true;
            fclose(tf);
        }
        else
            { iLoadedTiles[packTileID(tileX, tileY)] = false; }
        return result;
    }
