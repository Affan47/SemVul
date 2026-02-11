pull_varattnos_walker(Node *node, pull_varattnos_context *context)
{
	if (node == NULL)
		return false;
	if (IsA(node, Var))
	{
		Var		   *var = (Var *) node;

		if (var->varno == context->varno && var->varlevelsup == 0)
			context->varattnos =
				bms_add_member(context->varattnos,
						 var->varattno - FirstLowInvalidHeapAttributeNumber);
		return false;
	}


	Assert(!IsA(node, Query));

	return expression_tree_walker(node, pull_varattnos_walker,
								  (void *) context);
}
