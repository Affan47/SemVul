btreeSecbucketIdlist(AjPBtcache cache, ajulong pagepos,
                                    AjPList idlist)
{
    AjPStr tmpstr = NULL;

    AjPBtpage page  = NULL;
    AjPBtpage lpage = NULL;

    unsigned char *buf  = NULL;
    unsigned char *kptr = NULL;

    unsigned char *codeptr = NULL;

    ajuint  nodetype = 0U;
    ajuint  nentries = 0U;
    ajulong overflow = 0UL;
    ajulong pageoverflow = 0UL;
    ajuint  dirtysave = 0U;

    ajuint  i;
    ajuint  len  = 0U;


    page  = btreeSeccacheRead(cache,pagepos);
    lpage = page;
    dirtysave = lpage->dirty;
    lpage->dirty = BT_LOCK;
    lpage->lockfor = 1321;

    buf = lpage->buf;

    GBT_BUCKNODETYPE(buf,&nodetype);
    if(nodetype != BT_SECBUCKET)
	ajFatal("SecbucketIdlist: NodeType mismatch. "
                "Not secondary bucket (%u) cache %S",
		nodetype, cache->filename);

    GBT_BUCKNENTRIES(buf,&nentries);
    if(nentries > cache->snperbucket)
	ajFatal("SecbucketIdlist: Bucket too full page: %Lu "
                "entries: %u max: %u full cache %S",
                pagepos, nentries, cache->snperbucket, cache->filename);


    GBT_BUCKOVERFLOW(buf,&overflow);
    pageoverflow = overflow;

    kptr  = PBT_BUCKKEYLEN(buf);
    codeptr = kptr + (nentries * sizeof(ajuint));

    for(i=0;i<nentries;++i)
    {
	BT_GETAJUINT(kptr,&len);


        if(statSaveSecIdNext)
            tmpstr = statSaveSecId[--statSaveSecIdNext];
	ajStrAssignLenC(&tmpstr,(const char *)codeptr, len-1);

        ajListPushAppend(idlist, tmpstr);
        tmpstr = NULL;
	codeptr += len;

	kptr += sizeof(ajuint);
    }

    lpage->dirty = dirtysave;

    return pageoverflow;
}
