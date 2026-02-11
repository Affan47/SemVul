InsertTreeNode(TreeNode current, TreeNode new)
{
    TreeNode last = NULL, next;

    last = NULL;
    next = current->children;
    while (next)
    {
	int ab;

	if (! CheckNesting(new->loop, next->loop, &ab))
	    return ERROR;

	if (ab == A_INSIDE_B)
	{
	    if (new->children)
	    {
		DXSetError(ERROR_INTERNAL, "topology error");
		return ERROR;
	    }
	    else
		return InsertTreeNode(next, new);
	}
	else if (ab == B_INSIDE_A)
	{
	    TreeNode tmp = next;

	    if (last)
		last->sibling = next->sibling;
	    else
		current->children = next->sibling;

	    next = next->sibling;

	    tmp->sibling = new->children;
	    new->children = tmp;
	}
	else if (ab == AB_CROSS)
	{
	      DXSetError(ERROR_INTERNAL, "topology error");
	      return ERROR;
	}
	else
	{
	    last = next;
	    next = next->sibling;
	}
    }

    new->sibling = current->children;
    current->children = new;

    return OK;
}
