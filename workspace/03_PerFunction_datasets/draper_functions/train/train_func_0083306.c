ScanPgRelation(Oid targetRelId, bool indexOK)
{
	HeapTuple	pg_class_tuple;
	Relation	pg_class_desc;
	SysScanDesc pg_class_scan;
	ScanKeyData key[1];


	ScanKeyInit(&key[0],
				ObjectIdAttributeNumber,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(targetRelId));


	pg_class_desc = heap_open(RelationRelationId, AccessShareLock);
	pg_class_scan = systable_beginscan(pg_class_desc, ClassOidIndexId,
									   indexOK && criticalRelcachesBuilt,
									   SnapshotNow,
									   1, key);

	pg_class_tuple = systable_getnext(pg_class_scan);


	if (HeapTupleIsValid(pg_class_tuple))
		pg_class_tuple = heap_copytuple(pg_class_tuple);


	systable_endscan(pg_class_scan);
	heap_close(pg_class_desc, AccessShareLock);

	return pg_class_tuple;
}
