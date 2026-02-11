typenameType(ParseState *pstate, const TypeName *typename)
{
	Oid			typoid;
	HeapTuple	tup;

	typoid = LookupTypeName(pstate, typename);
	if (!OidIsValid(typoid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("type \"%s\" does not exist",
						TypeNameToString(typename)),
				 parser_errposition(pstate, typename->location)));
	tup = SearchSysCache(TYPEOID,
						 ObjectIdGetDatum(typoid),
						 0, 0, 0);
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", typoid);
	if (!((Form_pg_type) GETSTRUCT(tup))->typisdefined)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("type \"%s\" is only a shell",
						TypeNameToString(typename)),
				 parser_errposition(pstate, typename->location)));
	return (Type) tup;
}
