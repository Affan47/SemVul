ResetCatalogCaches(void)
{
	slist_iter	iter;

	CACHE1_elog(DEBUG2, "ResetCatalogCaches called");

	slist_foreach(iter, &CacheHdr->ch_caches)
	{
		CatCache   *cache = slist_container(CatCache, cc_next, iter.cur);

		ResetCatalogCache(cache);
	}

	CACHE1_elog(DEBUG2, "end of ResetCatalogCaches call");
}
