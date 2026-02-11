getOwnedSequences(Oid relid)
{
	List	   *result = NIL;
	Relation	depRel;
	ScanKeyData key[2];
	SysScanDesc scan;
	HeapTuple	tup;

	depRel = heap_open(DependRelationId, AccessShareLock);

	ScanKeyInit(&key[0],
				Anum_pg_depend_refclassid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationRelationId));
	ScanKeyInit(&key[1],
				Anum_pg_depend_refobjid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(relid));

	scan = systable_beginscan(depRel, DependReferenceIndexId, true,
							  NULL, 2, key);

	while (HeapTupleIsValid(tup = systable_getnext(scan)))
	{
		Form_pg_depend deprec = (Form_pg_depend) GETSTRUCT(tup);


		if (deprec->classid == RelationRelationId &&
			deprec->objsubid == 0 &&
			deprec->refobjsubid != 0 &&
			deprec->deptype == DEPENDENCY_AUTO &&
			get_rel_relkind(deprec->objid) == RELKIND_SEQUENCE)
		{
			result = lappend_oid(result, deprec->objid);
		}
	}

	systable_endscan(scan);

	heap_close(depRel, AccessShareLock);

	return result;
}
