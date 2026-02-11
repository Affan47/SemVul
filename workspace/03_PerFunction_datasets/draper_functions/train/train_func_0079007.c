btreePricacheControl(AjPBtcache cache, ajulong pagepos,
                                      AjBool isread)
{
    AjPBtpage ret      = NULL;


    if(pagepos < cache->totsize)
        ret = btreePricacheLocate(cache,pagepos);

    if(ret)
    {
	btreePricacheUnlink(cache,ret);
    }
    else
    {
	if(cache->prilistLength == cache->pricachesize)
	{
	    ret = btreePricacheLruUnlink(cache);

	    if(ret->dirty == BT_DIRTY)
		btreePricacheDestage(cache,ret);

	    if(isread || pagepos!=cache->totsize)
		btreePricacheFetch(cache,ret,pagepos);
            else
                btreePripageClear(cache, ret);
	}
	else
	{
	    ret = btreePripageNew(cache);

	    if(isread || pagepos!=cache->totsize)
		btreePricacheFetch(cache,ret,pagepos);
	}

	if(!isread)
	    ret->pagepos = pagepos;
	else
	    ret->dirty = BT_CLEAN;
    }

    btreePricacheMruAdd(cache,ret);

    if(!ajBtreePageIsPrimary(ret))
        ajWarn("btreePricacheControl secondary page %Lu '%s'",
               ret->pagepos, btreeNodetype(ret->buf));

    return ret;
}
