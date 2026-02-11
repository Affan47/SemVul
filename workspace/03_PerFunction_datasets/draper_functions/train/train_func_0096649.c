GetComment(Oid oid, Oid classoid, int32 subid)
{
	Relation	description;
	ScanKeyData skey[3];
	SysScanDesc sd;
	TupleDesc	tupdesc;
	HeapTuple	tuple;
	char	   *comment;


	ScanKeyInit(&skey[0],
				Anum_pg_description_objoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(oid));
	ScanKeyInit(&skey[1],
				Anum_pg_description_classoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(classoid));
	ScanKeyInit(&skey[2],
				Anum_pg_description_objsubid,
				BTEqualStrategyNumber, F_INT4EQ,
				Int32GetDatum(subid));

	description = heap_open(DescriptionRelationId, AccessShareLock);
	tupdesc = RelationGetDescr(description);

	sd = systable_beginscan(description, DescriptionObjIndexId, true,
							SnapshotNow, 3, skey);

	comment = NULL;
	while ((tuple = systable_getnext(sd)) != NULL)
	{
		Datum		value;
		bool		isnull;


		value = heap_getattr(tuple, Anum_pg_description_description, tupdesc, &isnull);
		if (!isnull)
			comment = TextDatumGetCString(value);
		break;
	}

	systable_endscan(sd);


	heap_close(description, AccessShareLock);

	return comment;
}
