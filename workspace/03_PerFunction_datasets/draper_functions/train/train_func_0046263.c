ApplySetting(Snapshot snapshot, Oid databaseid, Oid roleid,
			 Relation relsetting, GucSource source)
{
	SysScanDesc scan;
	ScanKeyData keys[2];
	HeapTuple	tup;

	ScanKeyInit(&keys[0],
				Anum_pg_db_role_setting_setdatabase,
				BTEqualStrategyNumber,
				F_OIDEQ,
				ObjectIdGetDatum(databaseid));
	ScanKeyInit(&keys[1],
				Anum_pg_db_role_setting_setrole,
				BTEqualStrategyNumber,
				F_OIDEQ,
				ObjectIdGetDatum(roleid));

	scan = systable_beginscan(relsetting, DbRoleSettingDatidRolidIndexId, true,
							  snapshot, 2, keys);
	while (HeapTupleIsValid(tup = systable_getnext(scan)))
	{
		bool		isnull;
		Datum		datum;

		datum = heap_getattr(tup, Anum_pg_db_role_setting_setconfig,
							 RelationGetDescr(relsetting), &isnull);
		if (!isnull)
		{
			ArrayType  *a = DatumGetArrayTypeP(datum);


			ProcessGUCArray(a, PGC_SUSET, source, GUC_ACTION_SET);
		}
	}

	systable_endscan(scan);
}
