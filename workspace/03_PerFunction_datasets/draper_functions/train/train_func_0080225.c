index_drop(Oid indexId)
{
	Oid			heapId;
	Relation	userHeapRelation;
	Relation	userIndexRelation;
	Relation	indexRelation;
	HeapTuple	tuple;
	bool		hasexprs;


	heapId = IndexGetRelation(indexId);
	userHeapRelation = heap_open(heapId, AccessExclusiveLock);

	userIndexRelation = index_open(indexId, AccessExclusiveLock);


	RelationDropStorage(userIndexRelation);


	index_close(userIndexRelation, NoLock);

	RelationForgetRelation(indexId);


	indexRelation = heap_open(IndexRelationId, RowExclusiveLock);

	tuple = SearchSysCache1(INDEXRELID, ObjectIdGetDatum(indexId));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for index %u", indexId);

	hasexprs = !heap_attisnull(tuple, Anum_pg_index_indexprs);

	simple_heap_delete(indexRelation, &tuple->t_self);

	ReleaseSysCache(tuple);
	heap_close(indexRelation, RowExclusiveLock);


	if (hasexprs)
		RemoveStatistics(indexId, 0);


	DeleteAttributeTuples(indexId);


	DeleteRelationTuple(indexId);


	CacheInvalidateRelcache(userHeapRelation);


	heap_close(userHeapRelation, NoLock);
}
