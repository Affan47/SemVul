GetConstraintByName(Oid relid, const char *conname)
{
	Relation	pg_constraint;
	HeapTuple	tuple;
	SysScanDesc scan;
	ScanKeyData skey[1];
	Oid			conOid = InvalidOid;


	pg_constraint = heap_open(ConstraintRelationId, AccessShareLock);

	ScanKeyInit(&skey[0],
				Anum_pg_constraint_conrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(relid));

	scan = systable_beginscan(pg_constraint, ConstraintRelidIndexId, true,
							  SnapshotNow, 1, skey);

	while (HeapTupleIsValid(tuple = systable_getnext(scan)))
	{
		Form_pg_constraint con = (Form_pg_constraint) GETSTRUCT(tuple);

		if (strcmp(NameStr(con->conname), conname) == 0)
		{
			if (OidIsValid(conOid))
				ereport(ERROR,
						(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("table \"%s\" has multiple constraints named \"%s\"",
						get_rel_name(relid), conname)));
			conOid = HeapTupleGetOid(tuple);
		}
	}

	systable_endscan(scan);


	if (!OidIsValid(conOid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("constraint \"%s\" for table \"%s\" does not exist",
						conname, get_rel_name(relid))));

	heap_close(pg_constraint, AccessShareLock);

	return conOid;
}
