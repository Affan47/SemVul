get_func_expr(FuncExpr *expr, deparse_context *context,
			  bool showimplicit)
{
	StringInfo	buf = context->buf;
	Oid			funcoid = expr->funcid;
	Oid			argtypes[FUNC_MAX_ARGS];
	int			nargs;
	ListCell   *l;


	if (expr->funcformat == COERCE_IMPLICIT_CAST && !showimplicit)
	{
		get_rule_expr_paren((Node *) linitial(expr->args), context,
							false, (Node *) expr);
		return;
	}


	if (expr->funcformat == COERCE_EXPLICIT_CAST ||
		expr->funcformat == COERCE_IMPLICIT_CAST)
	{
		Node	   *arg = linitial(expr->args);
		Oid			rettype = expr->funcresulttype;
		int32		coercedTypmod;


		(void) exprIsLengthCoercion((Node *) expr, &coercedTypmod);

		get_coercion_expr(arg, context,
						  rettype, coercedTypmod,
						  (Node *) expr);

		return;
	}


	nargs = 0;
	foreach(l, expr->args)
	{
		if (nargs >= FUNC_MAX_ARGS)
			ereport(ERROR,
					(errcode(ERRCODE_TOO_MANY_ARGUMENTS),
					 errmsg("too many arguments")));
		argtypes[nargs] = exprType((Node *) lfirst(l));
		nargs++;
	}

	appendStringInfo(buf, "%s(",
					 generate_function_name(funcoid, nargs, argtypes));
	get_rule_expr((Node *) expr->args, context, true);
	appendStringInfoChar(buf, ')');
}
