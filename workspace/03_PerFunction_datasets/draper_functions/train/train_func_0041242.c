init_sql_fcache(FmgrInfo *finfo)
{
	Oid			foid = finfo->fn_oid;
	Oid			rettype;
	HeapTuple	procedureTuple;
	Form_pg_proc procedureStruct;
	SQLFunctionCachePtr fcache;
	Oid		   *argOidVect;
	int			nargs;
	List	   *queryTree_list;
	Datum		tmp;
	bool		isNull;

	fcache = (SQLFunctionCachePtr) palloc0(sizeof(SQLFunctionCache));


	procedureTuple = SearchSysCache(PROCOID,
									ObjectIdGetDatum(foid),
									0, 0, 0);
	if (!HeapTupleIsValid(procedureTuple))
		elog(ERROR, "cache lookup failed for function %u", foid);
	procedureStruct = (Form_pg_proc) GETSTRUCT(procedureTuple);


	rettype = procedureStruct->prorettype;

	if (IsPolymorphicType(rettype))
	{
		rettype = get_fn_expr_rettype(finfo);
		if (rettype == InvalidOid)
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("could not determine actual result type for function declared to return type %s",
							format_type_be(procedureStruct->prorettype))));
	}

	fcache->rettype = rettype;


	get_typlenbyval(rettype, &fcache->typlen, &fcache->typbyval);


	fcache->readonly_func =
		(procedureStruct->provolatile != PROVOLATILE_VOLATILE);


	nargs = procedureStruct->pronargs;
	if (nargs > 0)
	{
		int			argnum;

		argOidVect = (Oid *) palloc(nargs * sizeof(Oid));
		memcpy(argOidVect,
			   procedureStruct->proargtypes.values,
			   nargs * sizeof(Oid));

		for (argnum = 0; argnum < nargs; argnum++)
		{
			Oid			argtype = argOidVect[argnum];

			if (IsPolymorphicType(argtype))
			{
				argtype = get_fn_expr_argtype(finfo, argnum);
				if (argtype == InvalidOid)
					ereport(ERROR,
							(errcode(ERRCODE_DATATYPE_MISMATCH),
							 errmsg("could not determine actual type of argument declared %s",
									format_type_be(argOidVect[argnum]))));
				argOidVect[argnum] = argtype;
			}
		}
	}
	else
		argOidVect = NULL;
	fcache->argtypes = argOidVect;


	tmp = SysCacheGetAttr(PROCOID,
						  procedureTuple,
						  Anum_pg_proc_prosrc,
						  &isNull);
	if (isNull)
		elog(ERROR, "null prosrc for function %u", foid);
	fcache->src = DatumGetCString(DirectFunctionCall1(textout, tmp));


	queryTree_list = pg_parse_and_rewrite(fcache->src, argOidVect, nargs);


	fcache->returnsTuple = check_sql_fn_retval(foid,
											   rettype,
											   queryTree_list,
											   &fcache->junkFilter);


	fcache->func_state = init_execution_state(queryTree_list,
											  fcache->readonly_func);

	ReleaseSysCache(procedureTuple);

	finfo->fn_extra = (void *) fcache;
}
