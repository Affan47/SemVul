loadMap(uint32 mapId, int32 x, int32 y)
    {

        if(!loadMapData(mapId))
            return false;


        MMapData* mmap = loadedMMaps[mapId];
        MANGOS_ASSERT(mmap->navMesh);


        uint32 packedGridPos = packTileID(x, y);
        if (mmap->mmapLoadedTiles.find(packedGridPos) != mmap->mmapLoadedTiles.end())
        {
            sLog.outError("MMAP:loadMap: Asked to load already loaded navmesh tile. %03u%02i%02i.mmtile", mapId, x, y);
            return false;
        }


        uint32 pathLen = sWorld.GetDataPath().length() + strlen("mmaps/%03i%02i%02i.mmtile")+1;
        char *fileName = new char[pathLen];
        snprintf(fileName, pathLen, (sWorld.GetDataPath()+"mmaps/%03i%02i%02i.mmtile").c_str(), mapId, x, y);

        FILE *file = fopen(fileName, "rb");
        if (!file)
        {
            sLog.outDebug("MMAP:loadMap: Could not open mmtile file '%s'", fileName);
            delete [] fileName;
            return false;
        }
        delete [] fileName;


        MmapTileHeader fileHeader;
        fread(&fileHeader, sizeof(MmapTileHeader), 1, file);

        if (fileHeader.mmapMagic != MMAP_MAGIC)
        {
            sLog.outError("MMAP:loadMap: Bad header in mmap %03u%02i%02i.mmtile", mapId, x, y);
            return false;
        }

        if (fileHeader.mmapVersion != MMAP_VERSION)
        {
            sLog.outError("MMAP:loadMap: %03u%02i%02i.mmtile was built with generator v%i, expected v%i",
                                                mapId, x, y, fileHeader.mmapVersion, MMAP_VERSION);
            return false;
        }

        unsigned char* data = (unsigned char*)dtAlloc(fileHeader.size, DT_ALLOC_PERM);
        MANGOS_ASSERT(data);

        size_t result = fread(data, fileHeader.size, 1, file);
        if(!result)
        {
            sLog.outError("MMAP:loadMap: Bad header or data in mmap %03u%02i%02i.mmtile", mapId, x, y);
            fclose(file);
            return false;
        }

        fclose(file);

        dtMeshHeader* header = (dtMeshHeader*)data;
        dtTileRef tileRef = 0;


        if(DT_SUCCESS == mmap->navMesh->addTile(data, fileHeader.size, DT_TILE_FREE_DATA, 0, &tileRef))
        {
            mmap->mmapLoadedTiles.insert(std::pair<uint32, dtTileRef>(packedGridPos, tileRef));
            ++loadedTiles;
            sLog.outDetail("MMAP:loadMap: Loaded mmtile %03i[%02i,%02i] into %03i[%02i,%02i]", mapId, x, y, mapId, header->x, header->y);
            return true;
        }
        else
        {
            sLog.outError("MMAP:loadMap: Could not load %03u%02i%02i.mmtile into navmesh", mapId, x, y);
            dtFree(data);
            return false;
        }

        return false;
    }
