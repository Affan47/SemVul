AlterDatabaseOwner(const char *dbname, Oid newOwnerId)
{
	HeapTuple	tuple;
	Relation	rel;
	ScanKeyData scankey;
	SysScanDesc scan;
	Form_pg_database datForm;


	rel = heap_open(DatabaseRelationId, RowExclusiveLock);
	ScanKeyInit(&scankey,
				Anum_pg_database_datname,
				BTEqualStrategyNumber, F_NAMEEQ,
				NameGetDatum(dbname));
	scan = systable_beginscan(rel, DatabaseNameIndexId, true,
							  SnapshotNow, 1, &scankey);
	tuple = systable_getnext(scan);
	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_DATABASE),
				 errmsg("database \"%s\" does not exist", dbname)));

	datForm = (Form_pg_database) GETSTRUCT(tuple);


	if (datForm->datdba != newOwnerId)
	{
		Datum		repl_val[Natts_pg_database];
		bool		repl_null[Natts_pg_database];
		bool		repl_repl[Natts_pg_database];
		Acl		   *newAcl;
		Datum		aclDatum;
		bool		isNull;
		HeapTuple	newtuple;


		if (!pg_database_ownercheck(HeapTupleGetOid(tuple), GetUserId()))
			aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_DATABASE,
						   dbname);


		check_is_member_of_role(GetUserId(), newOwnerId);


		if (!have_createdb_privilege())
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				   errmsg("permission denied to change owner of database")));

		memset(repl_null, false, sizeof(repl_null));
		memset(repl_repl, false, sizeof(repl_repl));

		repl_repl[Anum_pg_database_datdba - 1] = true;
		repl_val[Anum_pg_database_datdba - 1] = ObjectIdGetDatum(newOwnerId);


		aclDatum = heap_getattr(tuple,
								Anum_pg_database_datacl,
								RelationGetDescr(rel),
								&isNull);
		if (!isNull)
		{
			newAcl = aclnewowner(DatumGetAclP(aclDatum),
								 datForm->datdba, newOwnerId);
			repl_repl[Anum_pg_database_datacl - 1] = true;
			repl_val[Anum_pg_database_datacl - 1] = PointerGetDatum(newAcl);
		}

		newtuple = heap_modify_tuple(tuple, RelationGetDescr(rel), repl_val, repl_null, repl_repl);
		simple_heap_update(rel, &newtuple->t_self, newtuple);
		CatalogUpdateIndexes(rel, newtuple);

		heap_freetuple(newtuple);


		changeDependencyOnOwner(DatabaseRelationId, HeapTupleGetOid(tuple),
								newOwnerId);
	}

	systable_endscan(scan);


	heap_close(rel, NoLock);
}
