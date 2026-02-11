GetDefaultOpClass(Oid type_id, Oid am_id)
{
	int			nexact = 0;
	int			ncompatible = 0;
	Oid			exactOid = InvalidOid;
	Oid			compatibleOid = InvalidOid;
	Relation	rel;
	ScanKeyData skey[1];
	SysScanDesc scan;
	HeapTuple	tup;


	type_id = getBaseType(type_id);


	rel = heap_open(OperatorClassRelationId, AccessShareLock);

	ScanKeyInit(&skey[0],
				Anum_pg_opclass_opcamid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(am_id));

	scan = systable_beginscan(rel, OpclassAmNameNspIndexId, true,
							  SnapshotNow, 1, skey);

	while (HeapTupleIsValid(tup = systable_getnext(scan)))
	{
		Form_pg_opclass opclass = (Form_pg_opclass) GETSTRUCT(tup);

		if (opclass->opcdefault)
		{
			if (opclass->opcintype == type_id)
			{
				nexact++;
				exactOid = HeapTupleGetOid(tup);
			}
			else if (IsBinaryCoercible(type_id, opclass->opcintype))
			{
				ncompatible++;
				compatibleOid = HeapTupleGetOid(tup);
			}
		}
	}

	systable_endscan(scan);

	heap_close(rel, AccessShareLock);

	if (nexact == 1)
		return exactOid;
	if (nexact != 0)
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
		errmsg("there are multiple default operator classes for data type %s",
			   format_type_be(type_id))));
	if (ncompatible == 1)
		return compatibleOid;

	return InvalidOid;
}
