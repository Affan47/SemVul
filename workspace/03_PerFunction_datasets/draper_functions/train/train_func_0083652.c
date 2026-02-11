preprocess_expression(PlannerInfo *root, Node *expr, int kind)
{


	if (expr == NULL)
		return NULL;


	if (root->hasJoinRTEs && kind != EXPRKIND_VALUES)
		expr = flatten_join_alias_vars(root, expr);


	if (kind != EXPRKIND_VALUES &&
		(root->parse->jointree->fromlist != NIL ||
		 kind == EXPRKIND_QUAL ||
		 PlannerQueryLevel > 1))
		expr = eval_const_expressions(expr);


	if (kind == EXPRKIND_QUAL)
	{
		expr = (Node *) canonicalize_qual((Expr *) expr);

#ifdef OPTIMIZER_DEBUG
		printf("After canonicalize_qual()\n");
		pprint(expr);
#endif
	}


	if (root->parse->hasSubLinks)
		expr = SS_process_sublinks(expr, (kind == EXPRKIND_QUAL));


	if (PlannerQueryLevel > 1)
		expr = SS_replace_correlation_vars(expr);


	if (kind == EXPRKIND_QUAL)
		expr = (Node *) make_ands_implicit((Expr *) expr);

	return expr;
}
