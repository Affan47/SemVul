ScanQueryWalker(Node *node, ScanQueryWalkerContext *context)
{
	if (node == NULL)
		return false;
	if (IsA(node, SubLink))
	{
		SubLink    *sub = (SubLink *) node;


		ScanQueryForRelids((Query *) sub->subselect,
						   context->callback, context->arg);

	}


	return expression_tree_walker(node, ScanQueryWalker,
								  (void *) context);
}
