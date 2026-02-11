btreeWriteIdbucketEmpty(AjPBtcache cache, ajulong pagepos)
{
    AjPBtpage page      = NULL;
    unsigned char *buf  = NULL;
    ajuint   v   = 0U;
    ajulong lv   = 0UL;

    ajuint  nentries = 0U;
    ajulong overflow = 0UL;


    if(pagepos == cache->totsize)
    {
	page = btreePricacheBucketnew(cache);
	buf = page->buf;
	overflow = 0UL;
	lv = overflow;
	SBT_BUCKOVERFLOW(buf,lv);
    }
    else
    {
	page = btreePricacheRead(cache,pagepos);
	buf = page->buf;
	GBT_BUCKOVERFLOW(buf,&overflow);
    }

    v = BT_IDBUCKET;
    SBT_BUCKNODETYPE(buf,v);

    nentries = 0;
    v = nentries;
    SBT_BUCKNENTRIES(buf,v);

    lv = 0UL;
    SBT_BUCKOVERFLOW(buf,lv);

    page->dirty = BT_DIRTY;

    return;
}
