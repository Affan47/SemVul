replace_vars_with_subplan_refs_mutator(Node *node,
							 replace_vars_with_subplan_refs_context *context)
{
	Var		   *newvar;

	if (node == NULL)
		return NULL;
	if (IsA(node, Var))
	{
		Var		   *var = (Var *) node;

		newvar = search_indexed_tlist_for_var(var,
											  context->subplan_itlist,
											  context->subvarno);
		if (!newvar)
			elog(ERROR, "variable not found in subplan target list");
		return (Node *) newvar;
	}

	if (context->subplan_itlist->has_non_vars)
	{
		newvar = search_indexed_tlist_for_non_var(node,
												  context->subplan_itlist,
												  context->subvarno);
		if (newvar)
			return (Node *) newvar;
	}
	return expression_tree_mutator(node,
								   replace_vars_with_subplan_refs_mutator,
								   (void *) context);
}
