enum_cmp_internal(Oid arg1, Oid arg2, FunctionCallInfo fcinfo)
{
	TypeCacheEntry *tcache;


	if (arg1 == arg2)
		return 0;


	if ((arg1 & 1) == 0 && (arg2 & 1) == 0)
	{
		if (arg1 < arg2)
			return -1;
		else
			return 1;
	}


	tcache = (TypeCacheEntry *) fcinfo->flinfo->fn_extra;
	if (tcache == NULL)
	{
		HeapTuple	enum_tup;
		Form_pg_enum en;
		Oid			typeoid;


		enum_tup = SearchSysCache1(ENUMOID, ObjectIdGetDatum(arg1));
		if (!HeapTupleIsValid(enum_tup))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_BINARY_REPRESENTATION),
					 errmsg("invalid internal value for enum: %u",
							arg1)));
		en = (Form_pg_enum) GETSTRUCT(enum_tup);
		typeoid = en->enumtypid;
		ReleaseSysCache(enum_tup);

		tcache = lookup_type_cache(typeoid, 0);
		fcinfo->flinfo->fn_extra = (void *) tcache;
	}


	return compare_values_of_enum(tcache, arg1, arg2);
}
