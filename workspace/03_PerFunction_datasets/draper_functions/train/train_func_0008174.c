setHeapAlloced(void *p, StgWord8 i)
{
    MBlockMap *map = findMBlockMap(p);
    if(map == NULL)
    {
    	mblock_map_count++;
    	mblock_maps = stgReallocBytes(mblock_maps,
                                      sizeof(MBlockMap*) * mblock_map_count,
                                      "markHeapAlloced(1)");
	map = mblock_maps[mblock_map_count-1] =
            stgMallocBytes(sizeof(MBlockMap),"markHeapAlloced(2)");
        memset(map,0,sizeof(MBlockMap));
	map->addrHigh32 = (StgWord32) (((StgWord)p) >> 32);
    }

    map->lines[MBLOCK_MAP_LINE(p)] = i;

    {
        StgWord mblock;
        nat entry_no;

        mblock   = (StgWord)p >> MBLOCK_SHIFT;
        entry_no = mblock & (MBC_ENTRIES-1);
        mblock_cache[entry_no] = (mblock << 1) + i;
    }
}
