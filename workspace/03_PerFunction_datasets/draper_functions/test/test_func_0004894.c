make_new_heap(Oid OIDOldHeap, Oid NewTableSpace)
{
	TupleDesc	OldHeapDesc,
				tupdesc;
	char		NewHeapName[NAMEDATALEN];
	Oid			OIDNewHeap;
	Oid			toastid;
	Relation	OldHeap;
	HeapTuple	tuple;
	Datum		reloptions;
	bool		isNull;

	OldHeap = heap_open(OIDOldHeap, AccessExclusiveLock);
	OldHeapDesc = RelationGetDescr(OldHeap);


	tupdesc = CreateTupleDescCopy(OldHeapDesc);


	tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(OIDOldHeap));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for relation %u", OIDOldHeap);
	reloptions = SysCacheGetAttr(RELOID, tuple, Anum_pg_class_reloptions,
								 &isNull);
	if (isNull)
		reloptions = (Datum) 0;


	snprintf(NewHeapName, sizeof(NewHeapName), "pg_temp_%u", OIDOldHeap);

	OIDNewHeap = heap_create_with_catalog(NewHeapName,
										  RelationGetNamespace(OldHeap),
										  NewTableSpace,
										  InvalidOid,
										  InvalidOid,
										  InvalidOid,
										  OldHeap->rd_rel->relowner,
										  tupdesc,
										  NIL,
										  OldHeap->rd_rel->relkind,
										  false,
										  RelationIsMapped(OldHeap),
										  true,
										  0,
										  ONCOMMIT_NOOP,
										  reloptions,
										  false,
										  true);

	ReleaseSysCache(tuple);


	CommandCounterIncrement();


	toastid = OldHeap->rd_rel->reltoastrelid;
	if (OidIsValid(toastid))
	{

		tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(toastid));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for relation %u", toastid);
		reloptions = SysCacheGetAttr(RELOID, tuple, Anum_pg_class_reloptions,
									 &isNull);
		if (isNull)
			reloptions = (Datum) 0;

		AlterTableCreateToastTable(OIDNewHeap, reloptions);

		ReleaseSysCache(tuple);
	}

	heap_close(OldHeap, NoLock);

	return OIDNewHeap;
}
