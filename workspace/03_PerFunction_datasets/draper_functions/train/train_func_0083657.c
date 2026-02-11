get_oper_expr(OpExpr *expr, deparse_context *context)
{
	StringInfo	buf = context->buf;
	Oid			opno = expr->opno;
	List	   *args = expr->args;

	if (!PRETTY_PAREN(context))
		appendStringInfoChar(buf, '(');
	if (list_length(args) == 2)
	{

		Node	   *arg1 = (Node *) linitial(args);
		Node	   *arg2 = (Node *) lsecond(args);

		get_rule_expr_paren(arg1, context, true, (Node *) expr);
		appendStringInfo(buf, " %s ",
						 generate_operator_name(opno,
												exprType(arg1),
												exprType(arg2)));
		get_rule_expr_paren(arg2, context, true, (Node *) expr);
	}
	else
	{

		Node	   *arg = (Node *) linitial(args);
		HeapTuple	tp;
		Form_pg_operator optup;

		tp = SearchSysCache(OPEROID,
							ObjectIdGetDatum(opno),
							0, 0, 0);
		if (!HeapTupleIsValid(tp))
			elog(ERROR, "cache lookup failed for operator %u", opno);
		optup = (Form_pg_operator) GETSTRUCT(tp);
		switch (optup->oprkind)
		{
			case 'l':
				appendStringInfo(buf, "%s ",
								 generate_operator_name(opno,
														InvalidOid,
														exprType(arg)));
				get_rule_expr_paren(arg, context, true, (Node *) expr);
				break;
			case 'r':
				get_rule_expr_paren(arg, context, true, (Node *) expr);
				appendStringInfo(buf, " %s",
								 generate_operator_name(opno,
														exprType(arg),
														InvalidOid));
				break;
			default:
				elog(ERROR, "bogus oprkind: %d", optup->oprkind);
		}
		ReleaseSysCache(tp);
	}
	if (!PRETTY_PAREN(context))
		appendStringInfoChar(buf, ')');
}
