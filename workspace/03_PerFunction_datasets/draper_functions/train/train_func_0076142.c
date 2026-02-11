btreeKeyFind(AjPBtcache cache, const AjPStr key,
                           ajulong* treeblock)
{
    AjPBtpage page      = NULL;

    unsigned char *buf = NULL;

    ajulong blockno = 0UL;


    if(!cache->countunique)
	return ajFalse;

    page = btreeIdentFind(cache,key);

    buf = page->buf;

    blockno = btreeGetBlockS(cache, buf, key);

    return btreePribucketFindId(cache,blockno,key,treeblock);
}
