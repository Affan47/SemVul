fmgr_internal_validator(PG_FUNCTION_ARGS)
{
	Oid			funcoid = PG_GETARG_OID(0);
	HeapTuple	tuple;
	Form_pg_proc proc;
	bool		isnull;
	Datum		tmp;
	char	   *prosrc;


	tuple = SearchSysCache(PROCOID,
						   ObjectIdGetDatum(funcoid),
						   0, 0, 0);
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for function %u", funcoid);
	proc = (Form_pg_proc) GETSTRUCT(tuple);

	tmp = SysCacheGetAttr(PROCOID, tuple, Anum_pg_proc_prosrc, &isnull);
	if (isnull)
		elog(ERROR, "null prosrc");
	prosrc = TextDatumGetCString(tmp);

	if (fmgr_internal_function(prosrc) == InvalidOid)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("there is no built-in function named \"%s\"",
						prosrc)));

	ReleaseSysCache(tuple);

	PG_RETURN_VOID();
}
