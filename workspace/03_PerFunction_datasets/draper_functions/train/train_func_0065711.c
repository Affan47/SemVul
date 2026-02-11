PrepareToInvalidateCacheTuple(Relation relation,
							  HeapTuple tuple,
							void (*function) (int, uint32, ItemPointer, Oid))
{
	CatCache   *ccp;
	Oid			reloid;

	CACHE1_elog(DEBUG2, "PrepareToInvalidateCacheTuple: called");


	Assert(RelationIsValid(relation));
	Assert(HeapTupleIsValid(tuple));
	Assert(PointerIsValid(function));
	Assert(CacheHdr != NULL);

	reloid = RelationGetRelid(relation);


	for (ccp = CacheHdr->ch_caches; ccp; ccp = ccp->cc_next)
	{
		if (ccp->cc_reloid != reloid)
			continue;


		if (ccp->cc_tupdesc == NULL)
			CatalogCacheInitializeCache(ccp);

		(*function) (ccp->id,
					 CatalogCacheComputeTupleHashValue(ccp, tuple),
					 &tuple->t_self,
					 ccp->cc_relisshared ? (Oid) 0 : MyDatabaseId);
	}
}
