AlterRoleSet(AlterRoleSetStmt *stmt)
{
	HeapTuple	roletuple;
	Oid			databaseid = InvalidOid;

	roletuple = SearchSysCache1(AUTHNAME, PointerGetDatum(stmt->role));

	if (!HeapTupleIsValid(roletuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("role \"%s\" does not exist", stmt->role)));


	shdepLockAndCheckObject(AuthIdRelationId, HeapTupleGetOid(roletuple));


	if (((Form_pg_authid) GETSTRUCT(roletuple))->rolsuper)
	{
		if (!superuser())
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("must be superuser to alter superusers")));
	}
	else
	{
		if (!have_createrole_privilege() &&
			HeapTupleGetOid(roletuple) != GetUserId())
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("permission denied")));
	}


	if (stmt->database != NULL)
	{
		databaseid = get_database_oid(stmt->database, false);
		shdepLockAndCheckObject(DatabaseRelationId, databaseid);
	}

	AlterSetting(databaseid, HeapTupleGetOid(roletuple), stmt->setstmt);
	ReleaseSysCache(roletuple);
}
