unloadMap(uint32 mapId, int32 x, int32 y)
    {

        if (loadedMMaps.find(mapId) == loadedMMaps.end())
        {

            DEBUG_FILTER_LOG(LOG_FILTER_MAP_LOADING, "MMAP:unloadMap: Asked to unload not loaded navmesh map. %03u%02i%02i.mmtile", mapId, x, y);
            return false;
        }

        MMapData* mmap = loadedMMaps[mapId];


        uint32 packedGridPos = packTileID(x, y);
        if (mmap->mmapLoadedTiles.find(packedGridPos) == mmap->mmapLoadedTiles.end())
        {

            DEBUG_FILTER_LOG(LOG_FILTER_MAP_LOADING, "MMAP:unloadMap: Asked to unload not loaded navmesh tile. %03u%02i%02i.mmtile", mapId, x, y);
            return false;
        }

        dtTileRef tileRef = mmap->mmapLoadedTiles[packedGridPos];


        if (dtStatusFailed(mmap->navMesh->removeTile(tileRef, NULL, NULL)))
        {


            sLog.outError("MMAP:unloadMap: Could not unload %03u%02i%02i.mmtile from navmesh", mapId, x, y);
            MANGOS_ASSERT(false);
        }
        else
        {
            mmap->mmapLoadedTiles.erase(packedGridPos);
            --loadedTiles;
            DEBUG_FILTER_LOG(LOG_FILTER_MAP_LOADING, "MMAP:unloadMap: Unloaded mmtile %03i[%02i,%02i] from %03i", mapId, x, y, mapId);
            return true;
        }

        return false;
    }
