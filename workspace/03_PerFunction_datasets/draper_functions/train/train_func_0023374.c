btreeWriteIdbucket(AjPBtcache cache, const AjPIdbucket bucket,
                               ajulong pagepos)
{
    AjPBtpage page      = NULL;
    AjPBtpage lpage     = NULL;
    unsigned char *buf  = NULL;
    unsigned char *lbuf = NULL;
    ajuint  uv  = 0U;
    ajuint   v   = 0U;
    ajuint  i    = 0U;
    ajuint  iref = 0U;
    ajuint   len = 0U;
    ajulong lv   = 0UL;
    AjPBtId id  = NULL;

    ajuint nentries = 0U;
    ajulong overflow = 0UL;
    unsigned char *keyptr = NULL;
    unsigned char *lptr   = NULL;
    ajuint refskip = cache->refcount*BT_EXTRA;


    if(pagepos == cache->totsize)
    {
	page = btreePricacheBucketnew(cache);
	buf = page->buf;
    }
    else
    {
	page = btreePricacheRead(cache,pagepos);
	buf = page->buf;
	GBT_BUCKOVERFLOW(buf,&overflow);
    }

    v = BT_IDBUCKET;
    SBT_BUCKNODETYPE(buf,v);

    lbuf = buf;
    page->dirty = BT_LOCK;
    page->lockfor = 1091;
    lpage = page;

    nentries = bucket->Nentries;
    v = nentries;
    SBT_BUCKNENTRIES(buf,v);


    keyptr = PBT_BUCKKEYLEN(lbuf);

    for(i=0;i<nentries;++i)
    {


	id = bucket->Ids[i];

	len = BT_BUCKIDLEN(id->id) + refskip;
        v = len;
	BT_SETAJUINT(keyptr,v);
	keyptr += sizeof(ajuint);
    }


    lptr = keyptr;

    for(i=0;i<nentries;++i)
    {
	id = bucket->Ids[i];
	len = BT_BUCKIDLEN(id->id) + refskip;


	sprintf((char *)lptr,"%s",ajStrGetPtr(id->id));
	lptr += (ajStrGetLen(id->id) + 1);
        uv = id->dbno;
	BT_SETAJUINT(lptr,uv);
	lptr += sizeof(ajuint);
        uv = id->dups;
	BT_SETAJUINT(lptr,uv);
	lptr += sizeof(ajuint);
        lv = id->offset;
	BT_SETAJULONG(lptr,lv);
	lptr += sizeof(ajulong);

        if(cache->refcount)
        {
            for(iref=0; iref < cache->refcount; iref++)
            {
                lv = id->refoffsets[iref];
                BT_SETAJULONG(lptr,lv);
                lptr += sizeof(ajulong);
            }
        }
    }

    lv = 0UL;
    SBT_BUCKOVERFLOW(buf,lv);

    lpage->dirty = BT_DIRTY;

    return;
}
