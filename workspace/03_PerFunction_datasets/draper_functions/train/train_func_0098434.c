btreeNumbucketIdlist(AjPBtcache cache, ajulong pagepos,
                                    AjPList idlist)
{
    AjPBtNumId num      = NULL;
    AjPBtpage page      = NULL;
    unsigned char *buf  = NULL;
    unsigned char *pptr = NULL;
    ajuint  nodetype  = 0U;
    ajuint  nentries  = 0U;
    ajulong overflow  = 0UL;
    ajulong pageoverflow = 0UL;
    ajuint  dirtysave = 0U;

    ajuint  i;
    ajuint iref;


    if(pagepos == cache->secrootblock)
	ajFatal("NumbucketIdlist: cannot read bucket from root page cache %S",
                cache->filename);

    page = btreeSeccacheRead(cache,pagepos);
    dirtysave = page->dirty;
    page->dirty = BT_LOCK;
    page->lockfor = 1591;
    buf = page->buf;

    GBT_BUCKNODETYPE(buf,&nodetype);
    if(nodetype != BT_NUMBUCKET && nodetype != BT_IDBUCKET)
	ajFatal("NumbucketIdlist: Nodetype mismatch. "
                "Not bucket (%u) cache %S",
                nodetype, cache->filename);

    GBT_BUCKNENTRIES(buf,&nentries);
    if(nentries > cache->snperbucket)
	ajFatal("NumbucketIdlist: Bucket too full page: %Lu "
                "entries: %u max: %u cache %S",
                pagepos, nentries, cache->snperbucket, cache->filename);

    GBT_BUCKOVERFLOW(buf,&overflow);
    pageoverflow = overflow;

    pptr = PBT_BUCKKEYLEN(buf);

    for(i=0;i<nentries;++i)
    {
        AJNEW0(num);
        if(cache->refcount)
        {
            AJCNEW0(num->refoffsets, cache->refcount);
            num->refcount = cache->refcount;
        }

	BT_GETAJULONG(pptr,&num->offset);
	pptr += sizeof(ajulong);

        if(cache->refcount)
        {
            for(iref=0; iref < cache->refcount; iref++)
            {
                BT_GETAJULONG(pptr,&num->refoffsets[iref]);
                pptr += sizeof(ajulong);
            }
        }

	BT_GETAJUINT(pptr,&num->dbno);
	pptr += sizeof(ajuint);
        ajListPushAppend(idlist, num);
        num = NULL;
    }

    page->dirty = dirtysave;

    return pageoverflow;
}
