transformAExprOf(ParseState *pstate, A_Expr *a)
{
	Node	   *lexpr = a->lexpr;
	Const	   *result;
	ListCell   *telem;
	Oid			ltype,
				rtype;
	bool		matched = false;

	if (operator_precedence_warning)
		emit_precedence_warnings(pstate, PREC_GROUP_POSTFIX_IS, "IS",
								 lexpr, NULL,
								 a->location);

	lexpr = transformExprRecurse(pstate, lexpr);

	ltype = exprType(lexpr);
	foreach(telem, (List *) a->rexpr)
	{
		rtype = typenameTypeId(pstate, lfirst(telem));
		matched = (rtype == ltype);
		if (matched)
			break;
	}


	if (strcmp(strVal(linitial(a->name)), "<>") == 0)
		matched = (!matched);

	result = (Const *) makeBoolConst(matched, false);


	result->location = exprLocation((Node *) a);

	return (Node *) result;
}
