fmgr_sql_validator(PG_FUNCTION_ARGS)
{
	Oid			funcoid = PG_GETARG_OID(0);
	HeapTuple	tuple;
	Form_pg_proc proc;
	List	   *querytree_list;
	bool		isnull;
	Datum		tmp;
	char	   *prosrc;
	parse_error_callback_arg callback_arg;
	ErrorContextCallback sqlerrcontext;
	bool		haspolyarg;
	int			i;

	tuple = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcoid));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for function %u", funcoid);
	proc = (Form_pg_proc) GETSTRUCT(tuple);


	if (get_typtype(proc->prorettype) == TYPTYPE_PSEUDO &&
		proc->prorettype != RECORDOID &&
		proc->prorettype != VOIDOID &&
		!IsPolymorphicType(proc->prorettype))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
				 errmsg("SQL functions cannot return type %s",
						format_type_be(proc->prorettype))));


	haspolyarg = false;
	for (i = 0; i < proc->pronargs; i++)
	{
		if (get_typtype(proc->proargtypes.values[i]) == TYPTYPE_PSEUDO)
		{
			if (IsPolymorphicType(proc->proargtypes.values[i]))
				haspolyarg = true;
			else
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("SQL functions cannot have arguments of type %s",
							format_type_be(proc->proargtypes.values[i]))));
		}
	}


	if (check_function_bodies)
	{
		tmp = SysCacheGetAttr(PROCOID, tuple, Anum_pg_proc_prosrc, &isnull);
		if (isnull)
			elog(ERROR, "null prosrc");

		prosrc = TextDatumGetCString(tmp);


		callback_arg.proname = NameStr(proc->proname);
		callback_arg.prosrc = prosrc;

		sqlerrcontext.callback = sql_function_parse_error_callback;
		sqlerrcontext.arg = (void *) &callback_arg;
		sqlerrcontext.previous = error_context_stack;
		error_context_stack = &sqlerrcontext;


		if (!haspolyarg)
		{
			querytree_list = pg_parse_and_rewrite(prosrc,
												  proc->proargtypes.values,
												  proc->pronargs);
			(void) check_sql_fn_retval(funcoid, proc->prorettype,
									   querytree_list,
									   NULL, NULL);
		}
		else
			querytree_list = pg_parse_query(prosrc);

		error_context_stack = sqlerrcontext.previous;
	}

	ReleaseSysCache(tuple);

	PG_RETURN_VOID();
}
