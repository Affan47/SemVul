build_coercion_expression(Node *node, Oid funcId,
						  Oid targetTypeId, int32 targetTypMod,
						  CoercionForm cformat, bool isExplicit)
{
	HeapTuple	tp;
	Form_pg_proc procstruct;
	int			nargs;
	List	   *args;
	Const	   *cons;

	tp = SearchSysCache(PROCOID,
						ObjectIdGetDatum(funcId),
						0, 0, 0);
	if (!HeapTupleIsValid(tp))
		elog(ERROR, "cache lookup failed for function %u", funcId);
	procstruct = (Form_pg_proc) GETSTRUCT(tp);


	Assert(!procstruct->proretset);
	Assert(!procstruct->proisagg);
	nargs = procstruct->pronargs;
	Assert(nargs >= 1 && nargs <= 3);

	Assert(nargs < 2 || procstruct->proargtypes.values[1] == INT4OID);
	Assert(nargs < 3 || procstruct->proargtypes.values[2] == BOOLOID);

	ReleaseSysCache(tp);

	args = list_make1(node);

	if (nargs >= 2)
	{

		cons = makeConst(INT4OID,
						 sizeof(int32),
						 Int32GetDatum(targetTypMod),
						 false,
						 true);

		args = lappend(args, cons);
	}

	if (nargs == 3)
	{

		cons = makeConst(BOOLOID,
						 sizeof(bool),
						 BoolGetDatum(isExplicit),
						 false,
						 true);

		args = lappend(args, cons);
	}

	return (Node *) makeFuncExpr(funcId, targetTypeId, args, cformat);
}
