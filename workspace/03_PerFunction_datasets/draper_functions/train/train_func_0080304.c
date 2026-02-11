btreeNumInsert(AjPBtcache cache, const AjPBtNumId num,
                           AjPBtpage page)
{
    unsigned char *buf = NULL;
    ajulong numkey;
    AjPBtpage spage  = NULL;
    ajuint nkeys = 0;
    ajuint nodetype = 0;

    ajulong lblockno;
    ajulong rblockno;
    ajulong blockno;
    ajulong shift;
    ajuint n;


    (void) page;

    numkey = num->offset;

    spage = btreeNumFind(cache,numkey);
    buf = spage->buf;

    GBT_NKEYS(buf,&nkeys);
    GBT_NODETYPE(buf,&nodetype);

    if(!nkeys)
    {
	lblockno = cache->totsize;
	btreeWriteNumbucketEmpty(cache,lblockno);
	rblockno = cache->totsize;
	btreeWriteNumbucketEmpty(cache,rblockno);

	btreeWriteNumNodeSingle(cache,spage,numkey,lblockno,rblockno);

	btreeNumbucketAdd(cache,rblockno,num);

	return;
    }

    blockno = btreeGetBlockN(cache,buf,numkey);

    if(nodetype != BT_SECROOT)
	if((shift = btreeNumInsertShift(cache,&spage,numkey)))
	    blockno = shift;


    buf = spage->buf;
    n = btreeNumInNumbucket(cache,blockno);

    if(n == cache->snperbucket)
    {
	if(btreeReorderNumbuckets(cache,spage))
	{
            blockno = btreeGetBlockN(cache,buf,numkey);
	}
	else
	{
	    btreeNumSplitleaf(cache,spage);
	    spage = btreeNumFind(cache,numkey);
	    buf = spage->buf;

	    blockno = btreeGetBlockN(cache,buf,numkey);
	}
    }

    btreeNumbucketAdd(cache,blockno,num);

    return;
}
