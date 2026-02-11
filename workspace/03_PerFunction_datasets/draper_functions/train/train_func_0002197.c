make_scalar_array_op(ParseState *pstate, List *opname,
					 bool useOr,
					 Node *ltree, Node *rtree,
					 int location)
{
	Oid			ltypeId,
				rtypeId,
				atypeId,
				res_atypeId;
	Operator	tup;
	Form_pg_operator opform;
	Oid			actual_arg_types[2];
	Oid			declared_arg_types[2];
	List	   *args;
	Oid			rettype;
	ScalarArrayOpExpr *result;

	ltypeId = exprType(ltree);
	atypeId = exprType(rtree);


	if (atypeId == UNKNOWNOID)
		rtypeId = UNKNOWNOID;
	else
	{
		rtypeId = get_element_type(atypeId);
		if (!OidIsValid(rtypeId))
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				   errmsg("op ANY/ALL (array) requires array on right side"),
					 parser_errposition(pstate, location)));
	}


	tup = oper(pstate, opname, ltypeId, rtypeId, false, location);
	opform = (Form_pg_operator) GETSTRUCT(tup);

	args = list_make2(ltree, rtree);
	actual_arg_types[0] = ltypeId;
	actual_arg_types[1] = rtypeId;
	declared_arg_types[0] = opform->oprleft;
	declared_arg_types[1] = opform->oprright;


	rettype = enforce_generic_type_consistency(actual_arg_types,
											   declared_arg_types,
											   2,
											   opform->oprresult);


	if (rettype != BOOLOID)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
			 errmsg("op ANY/ALL (array) requires operator to yield boolean"),
				 parser_errposition(pstate, location)));
	if (get_func_retset(opform->oprcode))
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
		  errmsg("op ANY/ALL (array) requires operator not to return a set"),
				 parser_errposition(pstate, location)));


	res_atypeId = get_array_type(declared_arg_types[1]);
	if (!OidIsValid(res_atypeId))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("could not find array type for data type %s",
						format_type_be(declared_arg_types[1])),
				 parser_errposition(pstate, location)));
	actual_arg_types[1] = atypeId;
	declared_arg_types[1] = res_atypeId;


	make_fn_arguments(pstate, args, actual_arg_types, declared_arg_types);


	result = makeNode(ScalarArrayOpExpr);
	result->opno = oprid(tup);
	result->opfuncid = InvalidOid;
	result->useOr = useOr;
	result->args = args;


	check_pg_get_expr_args(pstate, opform->oprcode, args);

	ReleaseSysCache(tup);

	return (Expr *) result;
}
