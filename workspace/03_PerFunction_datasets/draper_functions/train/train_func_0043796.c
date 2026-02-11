transformAExprOpAny(ParseState *pstate, A_Expr *a)
{
	Node	   *lexpr = a->lexpr;
	Node	   *rexpr = a->rexpr;

	if (operator_precedence_warning)
		emit_precedence_warnings(pstate, PREC_GROUP_POSTFIX_OP,
								 strVal(llast(a->name)),
								 lexpr, NULL,
								 a->location);

	lexpr = transformExprRecurse(pstate, lexpr);
	rexpr = transformExprRecurse(pstate, rexpr);

	return (Node *) make_scalar_array_op(pstate,
										 a->name,
										 true,
										 lexpr,
										 rexpr,
										 a->location);
}
