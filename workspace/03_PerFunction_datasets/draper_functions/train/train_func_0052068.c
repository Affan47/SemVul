btreeNodeIsFullSec(const AjPBtcache cache, AjPBtpage page)
{
    unsigned char *buf = NULL;
    ajuint nkeys = 0;


    buf = page->buf;
    GBT_NKEYS(buf,&nkeys);

    if(nkeys == cache->sorder - 1)
	return ajTrue;

    return ajFalse;
}
