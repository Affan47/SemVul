AlterDatabase(AlterDatabaseStmt *stmt, bool isTopLevel)
{
	Relation	rel;
	HeapTuple	tuple,
				newtuple;
	ScanKeyData scankey;
	SysScanDesc scan;
	ListCell   *option;
	int			connlimit = -1;
	DefElem    *dconnlimit = NULL;
	DefElem    *dtablespace = NULL;
	Datum		new_record[Natts_pg_database];
	bool		new_record_nulls[Natts_pg_database];
	bool		new_record_repl[Natts_pg_database];


	foreach(option, stmt->options)
	{
		DefElem    *defel = (DefElem *) lfirst(option);

		if (strcmp(defel->defname, "connectionlimit") == 0)
		{
			if (dconnlimit)
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("conflicting or redundant options")));
			dconnlimit = defel;
		}
		else if (strcmp(defel->defname, "tablespace") == 0)
		{
			if (dtablespace)
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("conflicting or redundant options")));
			dtablespace = defel;
		}
		else
			elog(ERROR, "option \"%s\" not recognized",
				 defel->defname);
	}

	if (dtablespace)
	{

		Assert(!dconnlimit);

		PreventTransactionChain(isTopLevel, "ALTER DATABASE SET TABLESPACE");
		movedb(stmt->dbname, strVal(dtablespace->arg));
		return;
	}

	if (dconnlimit)
	{
		connlimit = intVal(dconnlimit->arg);
		if (connlimit < -1)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("invalid connection limit: %d", connlimit)));
	}


	rel = heap_open(DatabaseRelationId, RowExclusiveLock);
	ScanKeyInit(&scankey,
				Anum_pg_database_datname,
				BTEqualStrategyNumber, F_NAMEEQ,
				NameGetDatum(stmt->dbname));
	scan = systable_beginscan(rel, DatabaseNameIndexId, true,
							  SnapshotNow, 1, &scankey);
	tuple = systable_getnext(scan);
	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_DATABASE),
				 errmsg("database \"%s\" does not exist", stmt->dbname)));

	if (!pg_database_ownercheck(HeapTupleGetOid(tuple), GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_DATABASE,
					   stmt->dbname);


	MemSet(new_record, 0, sizeof(new_record));
	MemSet(new_record_nulls, false, sizeof(new_record_nulls));
	MemSet(new_record_repl, false, sizeof(new_record_repl));

	if (dconnlimit)
	{
		new_record[Anum_pg_database_datconnlimit - 1] = Int32GetDatum(connlimit);
		new_record_repl[Anum_pg_database_datconnlimit - 1] = true;
	}

	newtuple = heap_modify_tuple(tuple, RelationGetDescr(rel), new_record,
								 new_record_nulls, new_record_repl);
	simple_heap_update(rel, &tuple->t_self, newtuple);


	CatalogUpdateIndexes(rel, newtuple);

	systable_endscan(scan);


	heap_close(rel, NoLock);
}
