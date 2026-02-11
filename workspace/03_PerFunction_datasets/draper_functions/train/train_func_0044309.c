make_op(ParseState *pstate, List *opname, Node *ltree, Node *rtree,
		int location)
{
	Oid			ltypeId,
				rtypeId;
	Operator	tup;
	Form_pg_operator opform;
	Oid			actual_arg_types[2];
	Oid			declared_arg_types[2];
	int			nargs;
	List	   *args;
	Oid			rettype;
	OpExpr	   *result;


	if (rtree == NULL)
	{

		ltypeId = exprType(ltree);
		rtypeId = InvalidOid;
		tup = right_oper(pstate, opname, ltypeId, false, location);
	}
	else if (ltree == NULL)
	{

		rtypeId = exprType(rtree);
		ltypeId = InvalidOid;
		tup = left_oper(pstate, opname, rtypeId, false, location);
	}
	else
	{

		ltypeId = exprType(ltree);
		rtypeId = exprType(rtree);
		tup = oper(pstate, opname, ltypeId, rtypeId, false, location);
	}

	opform = (Form_pg_operator) GETSTRUCT(tup);


	if (!RegProcedureIsValid(opform->oprcode))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("operator is only a shell: %s",
						op_signature_string(opname,
											opform->oprkind,
											opform->oprleft,
											opform->oprright)),
				 parser_errposition(pstate, location)));


	if (rtree == NULL)
	{

		args = list_make1(ltree);
		actual_arg_types[0] = ltypeId;
		declared_arg_types[0] = opform->oprleft;
		nargs = 1;
	}
	else if (ltree == NULL)
	{

		args = list_make1(rtree);
		actual_arg_types[0] = rtypeId;
		declared_arg_types[0] = opform->oprright;
		nargs = 1;
	}
	else
	{

		args = list_make2(ltree, rtree);
		actual_arg_types[0] = ltypeId;
		actual_arg_types[1] = rtypeId;
		declared_arg_types[0] = opform->oprleft;
		declared_arg_types[1] = opform->oprright;
		nargs = 2;
	}


	rettype = enforce_generic_type_consistency(actual_arg_types,
											   declared_arg_types,
											   nargs,
											   opform->oprresult,
											   false);


	make_fn_arguments(pstate, args, actual_arg_types, declared_arg_types);


	result = makeNode(OpExpr);
	result->opno = oprid(tup);
	result->opfuncid = opform->oprcode;
	result->opresulttype = rettype;
	result->opretset = get_func_retset(opform->oprcode);
	result->args = args;
	result->location = location;

	ReleaseSysCache(tup);

	return (Expr *) result;
}
