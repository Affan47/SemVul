pg_get_function_identity_arguments(PG_FUNCTION_ARGS)
{
	Oid			funcid = PG_GETARG_OID(0);
	StringInfoData buf;
	HeapTuple	proctup;

	initStringInfo(&buf);

	proctup = SearchSysCache(PROCOID,
							 ObjectIdGetDatum(funcid),
							 0, 0, 0);
	if (!HeapTupleIsValid(proctup))
		elog(ERROR, "cache lookup failed for function %u", funcid);

	(void) print_function_arguments(&buf, proctup, false, false);

	ReleaseSysCache(proctup);

	PG_RETURN_TEXT_P(string_to_text(buf.data));
}
