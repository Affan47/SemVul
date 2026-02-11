ajBtreeIdentFetchHit(AjPBtcache cache, const AjPStr key,
                          AjPList hitlist)
{
    AjPBtpage page   = NULL;
    AjPIdbucket bucket = NULL;
    AjPBtHit  hit    = NULL;
    AjPBtId   tid    = NULL;

    unsigned char *buf = NULL;

    ajuint nentries = 0U;

    ajuint i;

    ajulong blockno = 0UL;
    AjBool found   = ajFalse;

    AjPStr keystr = NULL;


    if(!cache->countunique && !cache->countall)
        return;

    if(cache->refcount)
        ajWarn("ajBtreeIdentFetchHit called for cache '%S' "
               "with %u reference files",
               cache->filename, cache->refcount);

    keystr = ajStrNewS(key);
    ajStrFmtQuery(&keystr);

    page = btreeIdentFind(cache,keystr);
    buf = page->buf;

    blockno = btreeGetBlockS(cache,buf,keystr);

    bucket = btreeReadIdbucket(cache,blockno);

    nentries = bucket->Nentries;

    found = ajFalse;

    for(i=0;i<nentries;++i)
	if(!MAJSTRCMPS(bucket->Ids[i]->id, keystr))
	{
	    found = ajTrue;
	    break;
	}

    if(found)
    {
	tid = bucket->Ids[i];
	hit = ajBtreeHitNewId(tid);
    }

    ajStrDel(&keystr);

    if(!found)
    {
        btreeIdbucketDel(&bucket);
	return;
    }

    if(!tid->dups)
    {
        ajListPushAppend(hitlist,(void *)hit);
        hit = NULL;
    }
    else
    {
        btreeIdentFetchMultiHit(cache, tid->offset,
                                hitlist);
        ajBtreeHitDel(&hit);
    }

    btreeIdbucketDel(&bucket);

    return;
}
