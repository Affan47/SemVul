find_minimum_var_level_walker(Node *node,
							  find_minimum_var_level_context *context)
{
	if (node == NULL)
		return false;
	if (IsA(node, Var))
	{
		int			varlevelsup = ((Var *) node)->varlevelsup;


		varlevelsup -= context->sublevels_up;

		if (varlevelsup >= 0)
		{
			if (context->min_varlevel < 0 ||
				context->min_varlevel > varlevelsup)
			{
				context->min_varlevel = varlevelsup;


				if (varlevelsup == 0)
					return true;
			}
		}
	}


	if (IsA(node, Aggref))
	{
		int			agglevelsup = ((Aggref *) node)->agglevelsup;


		agglevelsup -= context->sublevels_up;

		if (agglevelsup >= 0)
		{
			if (context->min_varlevel < 0 ||
				context->min_varlevel > agglevelsup)
			{
				context->min_varlevel = agglevelsup;


				if (agglevelsup == 0)
					return true;
			}
		}
	}
	if (IsA(node, Query))
	{

		bool		result;

		context->sublevels_up++;
		result = query_tree_walker((Query *) node,
								   find_minimum_var_level_walker,
								   (void *) context,
								   0);
		context->sublevels_up--;
		return result;
	}
	return expression_tree_walker(node,
								  find_minimum_var_level_walker,
								  (void *) context);
}
