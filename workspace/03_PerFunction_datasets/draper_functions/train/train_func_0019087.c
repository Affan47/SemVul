btreeWriteNumNode(AjPBtcache cache, AjPBtpage spage,
			      const ajulong *keys, const ajulong *ptrs,
			      ajuint nkeys)
{
    unsigned char *pptr   = NULL;
    unsigned char *buf;

    ajuint tnkeys = 0U;
    ajuint totlen = 0U;

    ajulong lv       = 0UL;
    ajulong overflow = 0UL;
    ajuint i;


    (void) cache;

#if AJINDEX_DEBUG
    ajDebug("btreeWriteNumNode %Lu nkeys:%u\n", spage->pagepos, nkeys);
#endif

    buf = spage->buf;

    tnkeys = nkeys;
    SBT_NKEYS(buf,tnkeys);
    totlen = 0U;
    SBT_TOTLEN(buf, totlen);

    pptr = PBT_KEYLEN(buf);


    for(i=0U;i<nkeys;++i)
    {
	lv = keys[i];
	BT_SETAJULONG(pptr,lv);
	pptr += sizeof(ajulong);
    }

    for(i=0;i<nkeys;++i)
    {
	lv = ptrs[i];
	BT_SETAJULONG(pptr,lv);
	pptr += sizeof(ajulong);
    }

    lv = ptrs[i];
    BT_SETAJULONG(pptr,lv);
    pptr += sizeof(ajulong);

    overflow = 0UL;
    SBT_OVERFLOW(buf,overflow);

    spage->dirty = BT_DIRTY;

    return;
}
