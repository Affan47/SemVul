dropdb(const char *dbname, bool missing_ok)
{
	Oid			db_id;
	bool		db_istemplate;
	Relation	pgdbrel;
	HeapTuple	tup;


	pgdbrel = heap_open(DatabaseRelationId, RowExclusiveLock);

	if (!get_db_info(dbname, AccessExclusiveLock, &db_id, NULL, NULL,
					 &db_istemplate, NULL, NULL, NULL, NULL))
	{
		if (!missing_ok)
		{
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_DATABASE),
					 errmsg("database \"%s\" does not exist", dbname)));
		}
		else
		{

			heap_close(pgdbrel, RowExclusiveLock);
			ereport(NOTICE,
					(errmsg("database \"%s\" does not exist, skipping",
							dbname)));
			return;
		}
	}


	if (!pg_database_ownercheck(db_id, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_DATABASE,
					   dbname);


	if (db_istemplate)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot drop a template database")));


	if (db_id == MyDatabaseId)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_IN_USE),
				 errmsg("cannot drop the currently open database")));


	if (CheckOtherDBBackends(db_id))
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_IN_USE),
				 errmsg("database \"%s\" is being accessed by other users",
						dbname)));


	tup = SearchSysCache(DATABASEOID,
						 ObjectIdGetDatum(db_id),
						 0, 0, 0);
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for database %u", db_id);

	simple_heap_delete(pgdbrel, &tup->t_self);

	ReleaseSysCache(tup);


	DeleteSharedComments(db_id, DatabaseRelationId);


	dropDatabaseDependencies(db_id);


	DropDatabaseBuffers(db_id);


	FreeSpaceMapForgetDatabase(db_id);


	pgstat_drop_database(db_id);


	ForgetDatabaseFsyncRequests(db_id);


	RequestCheckpoint(CHECKPOINT_IMMEDIATE | CHECKPOINT_FORCE | CHECKPOINT_WAIT);


	remove_dbtablespaces(db_id);


	heap_close(pgdbrel, NoLock);


	database_file_update_needed();
}
