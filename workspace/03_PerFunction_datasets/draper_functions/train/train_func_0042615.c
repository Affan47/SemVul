DXGetCacheEntryV(char *function, int key, int n, Object *in)
{
    char	 tag[8+3];
    gvar	 *entry;
    int		 i;
    EXCRC        inTags[100];
    EXCRC 	outTag;
    Object	out = NULL;

    if (_dxd_exCacheDict == NULL)
	return (NULL);

    for (i = 0; i < n && i < 100; ++i)
	inTags[i] = DXGetObjectTag(in[i]);
    outTag = _dxf_ExGenCacheTag(function, key, n, inTags);

    tag[0] = 'U';
    int32tohex(tag+1, outTag);

    entry = (gvar *)_dxf_ExDictionarySearch (_dxd_exCacheDict, tag);
    if (entry) {
	ExTimestamp(entry);
	out = DXReference (entry->obj);
	ExDelete(entry);
    }

    return (out);
}
