InitCatCachePhase2(CatCache *cache, bool touch_index)
{
	if (cache->cc_tupdesc == NULL)
		CatalogCacheInitializeCache(cache);

	if (touch_index &&
		cache->id != AMOID &&
		cache->id != AMNAME)
	{
		Relation	idesc;

		idesc = index_open(cache->cc_indexoid, AccessShareLock);
		index_close(idesc, AccessShareLock);
	}
}
