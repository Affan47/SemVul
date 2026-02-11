DropCastById(Oid castOid)
{
	Relation	relation;
	ScanKeyData scankey;
	SysScanDesc scan;
	HeapTuple	tuple;

	relation = heap_open(CastRelationId, RowExclusiveLock);

	ScanKeyInit(&scankey,
				ObjectIdAttributeNumber,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(castOid));
	scan = systable_beginscan(relation, CastOidIndexId, true,
							  SnapshotNow, 1, &scankey);

	tuple = systable_getnext(scan);
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "could not find tuple for cast %u", castOid);
	simple_heap_delete(relation, &tuple->t_self);

	systable_endscan(scan);
	heap_close(relation, RowExclusiveLock);
}
