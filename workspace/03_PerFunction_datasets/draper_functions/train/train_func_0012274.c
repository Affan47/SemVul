find_oper_cache_entry(OprCacheKey *key)
{
	OprCacheEntry *oprentry;

	if (OprCacheHash == NULL)
	{

		HASHCTL		ctl;

		MemSet(&ctl, 0, sizeof(ctl));
		ctl.keysize = sizeof(OprCacheKey);
		ctl.entrysize = sizeof(OprCacheEntry);
		ctl.hash = tag_hash;
		OprCacheHash = hash_create("Operator lookup cache", 256,
								   &ctl, HASH_ELEM | HASH_FUNCTION);


		CacheRegisterSyscacheCallback(OPERNAMENSP,
									  InvalidateOprCacheCallBack,
									  (Datum) 0);
		CacheRegisterSyscacheCallback(CASTSOURCETARGET,
									  InvalidateOprCacheCallBack,
									  (Datum) 0);
	}


	oprentry = (OprCacheEntry *) hash_search(OprCacheHash,
											 (void *) key,
											 HASH_FIND, NULL);
	if (oprentry == NULL)
		return InvalidOid;

	return oprentry->opr_oid;
}
