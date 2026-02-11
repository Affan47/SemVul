_LoadTile(uint32 gx, uint32 gy, uint32 m)
{

    _mapsLoaded = false;
    std::string mapname = MapID2Name(m);
    logdebug("Mapname: %s",mapname.c_str());
    char buf[255];
    MemoryDataHolder::MakeMapFilename(buf,m,mapname,gx,gy);
    if(!_tiles->TileExists(gx,gy))
    {
        if(MemoryDataHolder::FileExists(buf))
        {
            logerror("MapMgr: Tile (%u, %u) exists not in WDT, but as file?!",gx,gy);

        }
        else
        {
            logerror("MAPMGR: Not loading MapTile (%u, %u) map %u, no entry in WDT tile map",gx,gy,m);
            return;
        }
    }

    if( !_tiles->GetTile(gx,gy) )
    {
        MemoryDataHolder::MemoryDataResult mdr = MemoryDataHolder::GetFileBasic(buf);
        if(mdr.flags & MemoryDataHolder::MDH_FILE_OK && mdr.data.size)
        {
            ByteBuffer bb(mdr.data.size);
            bb.append(mdr.data.ptr,mdr.data.size);
            MemoryDataHolder::Delete(buf);
            ADTFile *adt = new ADTFile();
            if(adt->LoadMem(bb))
            {
              logdebug("MAPMGR: Loaded ADT '%s'",buf);
              MapTile *tile = new MapTile();
              tile->ImportFromADT(adt);
              _tiles->SetTile(tile,gx,gy);
            }
            else
            {
              logerror("MAPMGR: Error loading ADT '%s'",buf);
            }
            delete adt;
            logdebug("MAPMGR: Imported MapTile (%u, %u) for map %u",gx,gy,m);
        }
        else
        {
            logerror("MAPMGR: Loading ADT '%s' failed!",buf);
        }
    }
    else
    {
        logdebug("MAPMGR: No need to load MapTile (%u, %u) map %u",gx,gy,m);
    }
}
