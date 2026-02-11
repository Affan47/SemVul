prepare_sql_fn_parse_info(HeapTuple procedureTuple,
						  Node *call_expr,
						  Oid inputCollation)
{
	SQLFunctionParseInfoPtr pinfo;
	Form_pg_proc procedureStruct = (Form_pg_proc) GETSTRUCT(procedureTuple);
	int			nargs;

	pinfo = (SQLFunctionParseInfoPtr) palloc0(sizeof(SQLFunctionParseInfo));


	pinfo->collation = inputCollation;


	pinfo->nargs = nargs = procedureStruct->pronargs;
	if (nargs > 0)
	{
		Oid		   *argOidVect;
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
				argtype = get_call_expr_argtype(call_expr, argnum);
				if (argtype == InvalidOid)
					ereport(ERROR,
							(errcode(ERRCODE_DATATYPE_MISMATCH),
							 errmsg("could not determine actual type of argument declared %s",
									format_type_be(argOidVect[argnum]))));
				argOidVect[argnum] = argtype;
			}
		}

		pinfo->argtypes = argOidVect;
	}

	return pinfo;
}
