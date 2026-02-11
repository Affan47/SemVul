btreeWriteNumbucketEmpty(AjPBtcache cache, ajulong pagepos)
{
    AjPBtpage page      = NULL;
    unsigned char *buf  = NULL;

    ajuint   v   = 0U;
    ajulong lv   = 0UL;
    ajulong overflow = 0UL;


    if(pagepos == cache->totsize)
    {
	page = btreeSeccacheBucketnew(cache);
	buf = page->buf;
	overflow = 0UL;
	lv = overflow;
	SBT_BUCKOVERFLOW(buf,lv);
    }
    else
    {
	page = btreeSeccacheRead(cache,pagepos);
	buf = page->buf;
	GBT_BUCKOVERFLOW(buf,&overflow);
    }

    v = BT_NUMBUCKET;
    SBT_BUCKNODETYPE(buf,v);
    page->dirty = BT_LOCK;
    page->lockfor = 1581;

    v = 0U;
    SBT_BUCKNENTRIES(buf,v);

    lv = 0UL;
    SBT_BUCKOVERFLOW(buf,lv);

    page->dirty = BT_DIRTY;

    return;
}
