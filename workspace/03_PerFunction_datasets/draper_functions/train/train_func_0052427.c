heap_truncate_find_FKs(List *relationIds)
{
	List	   *result = NIL;
	Relation	fkeyRel;
	SysScanDesc fkeyScan;
	HeapTuple	tuple;


	fkeyRel = heap_open(ConstraintRelationId, AccessShareLock);

	fkeyScan = systable_beginscan(fkeyRel, InvalidOid, false,
								  SnapshotNow, 0, NULL);

	while (HeapTupleIsValid(tuple = systable_getnext(fkeyScan)))
	{
		Form_pg_constraint con = (Form_pg_constraint) GETSTRUCT(tuple);


		if (con->contype != CONSTRAINT_FOREIGN)
			continue;


		if (!list_member_oid(relationIds, con->confrelid))
			continue;


		if (!list_member_oid(relationIds, con->conrelid))
			result = insert_ordered_unique_oid(result, con->conrelid);
	}

	systable_endscan(fkeyScan);
	heap_close(fkeyRel, AccessShareLock);

	return result;
}
