CatalogCacheFlushRelation(Oid relId)
{
	CatCache   *cache;

	CACHE2_elog(DEBUG2, "CatalogCacheFlushRelation called for %u", relId);

	for (cache = CacheHdr->ch_caches; cache; cache = cache->cc_next)
	{
		int			i;


		if (cache->cc_tupdesc == NULL)
			continue;


		if (cache->cc_tupdesc->attrs[0]->attrelid == relId)
		{

			ResetCatalogCache(cache);
			continue;
		}


		if (cache->cc_reloidattr == 0)
			continue;


		for (i = 0; i < cache->cc_nbuckets; i++)
		{
			Dlelem	   *elt,
					   *nextelt;

			for (elt = DLGetHead(&cache->cc_bucket[i]); elt; elt = nextelt)
			{
				CatCTup    *ct = (CatCTup *) DLE_VAL(elt);
				Oid			tupRelid;

				nextelt = DLGetSucc(elt);


				if (ct->negative)
					continue;

				if (cache->cc_reloidattr == ObjectIdAttributeNumber)
					tupRelid = HeapTupleGetOid(&ct->tuple);
				else
				{
					bool		isNull;

					tupRelid =
						DatumGetObjectId(fastgetattr(&ct->tuple,
													 cache->cc_reloidattr,
													 cache->cc_tupdesc,
													 &isNull));
					Assert(!isNull);
				}

				if (tupRelid == relId)
				{
					if (ct->refcount > 0 ||
						(ct->c_list && ct->c_list->refcount > 0))
					{
						ct->dead = true;

						if (ct->c_list)
							ct->c_list->dead = true;
					}
					else
						CatCacheRemoveCTup(cache, ct);
#ifdef CATCACHE_STATS
					cache->cc_invals++;
#endif
				}
			}
		}
	}

	CACHE1_elog(DEBUG2, "end of CatalogCacheFlushRelation call");
}
