shdepChangeDep(Relation sdepRel,
			   Oid classid, Oid objid, int32 objsubid,
			   Oid refclassid, Oid refobjid,
			   SharedDependencyType deptype)
{
	Oid			dbid = classIdGetDbId(classid);
	HeapTuple	oldtup = NULL;
	HeapTuple	scantup;
	ScanKeyData key[4];
	SysScanDesc scan;


	shdepLockAndCheckObject(refclassid, refobjid);


	ScanKeyInit(&key[0],
				Anum_pg_shdepend_dbid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(dbid));
	ScanKeyInit(&key[1],
				Anum_pg_shdepend_classid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(classid));
	ScanKeyInit(&key[2],
				Anum_pg_shdepend_objid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(objid));
	ScanKeyInit(&key[3],
				Anum_pg_shdepend_objsubid,
				BTEqualStrategyNumber, F_INT4EQ,
				Int32GetDatum(objsubid));

	scan = systable_beginscan(sdepRel, SharedDependDependerIndexId, true,
							  SnapshotNow, 4, key);

	while ((scantup = systable_getnext(scan)) != NULL)
	{

		if (((Form_pg_shdepend) GETSTRUCT(scantup))->deptype != deptype)
			continue;

		if (oldtup)
			elog(ERROR,
			   "multiple pg_shdepend entries for object %u/%u/%d deptype %c",
				 classid, objid, objsubid, deptype);
		oldtup = heap_copytuple(scantup);
	}

	systable_endscan(scan);

	if (isSharedObjectPinned(refclassid, refobjid, sdepRel))
	{

		if (oldtup)
			simple_heap_delete(sdepRel, &oldtup->t_self);
	}
	else if (oldtup)
	{

		Form_pg_shdepend shForm = (Form_pg_shdepend) GETSTRUCT(oldtup);


		shForm->refclassid = refclassid;
		shForm->refobjid = refobjid;

		simple_heap_update(sdepRel, &oldtup->t_self, oldtup);


		CatalogUpdateIndexes(sdepRel, oldtup);
	}
	else
	{

		Datum		values[Natts_pg_shdepend];
		bool		nulls[Natts_pg_shdepend];

		memset(nulls, false, sizeof(nulls));

		values[Anum_pg_shdepend_dbid - 1] = ObjectIdGetDatum(dbid);
		values[Anum_pg_shdepend_classid - 1] = ObjectIdGetDatum(classid);
		values[Anum_pg_shdepend_objid - 1] = ObjectIdGetDatum(objid);
		values[Anum_pg_shdepend_objsubid - 1] = Int32GetDatum(objsubid);

		values[Anum_pg_shdepend_refclassid - 1] = ObjectIdGetDatum(refclassid);
		values[Anum_pg_shdepend_refobjid - 1] = ObjectIdGetDatum(refobjid);
		values[Anum_pg_shdepend_deptype - 1] = CharGetDatum(deptype);


		oldtup = heap_form_tuple(RelationGetDescr(sdepRel), values, nulls);
		simple_heap_insert(sdepRel, oldtup);


		CatalogUpdateIndexes(sdepRel, oldtup);
	}

	if (oldtup)
		heap_freetuple(oldtup);
}
