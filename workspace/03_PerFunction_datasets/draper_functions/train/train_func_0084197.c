DXSetCacheEntryV(Object out, double cost, char *function,
		     int key, int n, Object *in)
{
    char	 tag[8+3];
    gvar	 *entry;
    int		 i;
    EXCRC   	inTags[100];
    EXCRC	outTag;


    if (_dxd_exCacheDict == NULL)
	return (OK);


    ExDebug("*1","In DXSetCacheEntryV with cost = %g and cache attr = %d",
            cost,_dxd_exCurrentFunc ? _dxd_exCurrentFunc->excache: 1);

    if (cost < CACHE_PERMANENT)
      if (_dxd_exCurrentFunc && !_dxd_exCurrentFunc->excache) {
        DXWarning("#4860",function);
        return OK;
    }

    for (i = 0; i < n && i < 100; ++i)
	inTags[i] = DXGetObjectTag(in[i]);
    outTag = _dxf_ExGenCacheTag(function, key, n, inTags);

    tag[0] = 'U';
    int32tohex(tag+1, outTag);

    if (out == NULL) {
	_dxf_ExDictionaryDelete(_dxd_exCacheDict, tag);
	return (OK);
    }
    else
    {
	entry = _dxf_ExCreateGvar(GV_CACHE);
	if (entry == NULL)
	    return (ERROR);

	_dxf_ExDefineGvar(entry, out);
	entry->cost   = cost;

	entry->procId = exJID;
	ExTimestamp(entry);

	return (_dxf_ExDictionaryInsert (_dxd_exCacheDict, tag, (EXObj)entry));
    }
}
