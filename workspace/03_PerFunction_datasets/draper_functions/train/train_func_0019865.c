transformAExprOp(ParseState *pstate, A_Expr *a)
{
	Node	   *lexpr = a->lexpr;
	Node	   *rexpr = a->rexpr;
	Node	   *result;

	if (operator_precedence_warning)
	{
		int			opgroup;
		const char *opname;

		opgroup = operator_precedence_group((Node *) a, &opname);
		if (opgroup > 0)
			emit_precedence_warnings(pstate, opgroup, opname,
									 lexpr, rexpr,
									 a->location);
	}


	if (Transform_null_equals &&
		list_length(a->name) == 1 &&
		strcmp(strVal(linitial(a->name)), "=") == 0 &&
		(exprIsNullConstant(lexpr) || exprIsNullConstant(rexpr)) &&
		(!IsA(lexpr, CaseTestExpr) &&!IsA(rexpr, CaseTestExpr)))
	{
		NullTest   *n = makeNode(NullTest);

		n->nulltesttype = IS_NULL;
		n->location = a->location;

		if (exprIsNullConstant(lexpr))
			n->arg = (Expr *) rexpr;
		else
			n->arg = (Expr *) lexpr;

		result = transformExprRecurse(pstate, (Node *) n);
	}
	else if (lexpr && IsA(lexpr, RowExpr) &&
			 rexpr && IsA(rexpr, SubLink) &&
			 ((SubLink *) rexpr)->subLinkType == EXPR_SUBLINK)
	{


		SubLink    *s = (SubLink *) rexpr;

		s->subLinkType = ROWCOMPARE_SUBLINK;
		s->testexpr = lexpr;
		s->operName = a->name;
		s->location = a->location;
		result = transformExprRecurse(pstate, (Node *) s);
	}
	else if (lexpr && IsA(lexpr, RowExpr) &&
			 rexpr && IsA(rexpr, RowExpr))
	{

		lexpr = transformExprRecurse(pstate, lexpr);
		rexpr = transformExprRecurse(pstate, rexpr);
		Assert(IsA(lexpr, RowExpr));
		Assert(IsA(rexpr, RowExpr));

		result = make_row_comparison_op(pstate,
										a->name,
										((RowExpr *) lexpr)->args,
										((RowExpr *) rexpr)->args,
										a->location);
	}
	else
	{

		lexpr = transformExprRecurse(pstate, lexpr);
		rexpr = transformExprRecurse(pstate, rexpr);

		result = (Node *) make_op(pstate,
								  a->name,
								  lexpr,
								  rexpr,
								  a->location);
	}

	return result;
}
