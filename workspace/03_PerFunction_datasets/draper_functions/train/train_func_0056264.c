__ExReclaimMemory (ulong nbytes)
{
    EXObj	obj;
    gvar	*gv;
    int		skipped;
    char	*key;
    CacheTagList pkg;
    uint32	 *ctp;

    _dxf_ExDictionaryBeginIterateSorted(_dxd_exCacheDict, 0);

    pkg.numtags = 0;
    ctp = pkg.ct;

    while (NULL !=
	(obj = _dxf_ExDictionaryIterateSorted(_dxd_exCacheDict, &key)))
    {
	gv = (gvar *)obj;

	if (gv->type == GV_UNRESOLVED || gv->cost == CACHE_PERMANENT)
	    continue;

	ExDebug ("2", "Free %s from cache", key);

        if(key[0] == 'X') {
            *ctp = strtoul(key+1, NULL, 16);
	    if (_dxf_ExDictionaryDelete (_dxd_exCacheDict, key) == OK)
	    {
                pkg.numtags++;
                ctp++;

		if (pkg.numtags >= N_CACHETAGLIST_ITEMS)
		{
		    _dxf_ExDistributeMsg(DM_EVICTCACHELIST, (Pointer)&pkg,
                             sizeof(CacheTagList), TOPEERS);
		    pkg.numtags = 0;
		    ctp = pkg.ct;
		}
            }
        }
        else
	    _dxf_ExDictionaryDelete(_dxd_exCacheDict, key);

	nDeleted ++;

	if (nbytes <= DXMaxFreedBlock())
	    break;
    }

    skipped = (obj) ? 1 : 0;

    if(pkg.numtags > 0)
        _dxf_ExDistributeMsg(DM_EVICTCACHELIST, (Pointer)&pkg,
                             sizeof(CacheTagList), TOPEERS);

    _dxf_ExDictionaryEndIterate (_dxd_exCacheDict);

    return skipped;
}
