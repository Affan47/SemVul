anjuta_token_prepend_child (AnjutaToken *parent, AnjutaToken *children)
{
	AnjutaToken *child;
	AnjutaToken *last = NULL;

	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (children != NULL, NULL);


	for (child = children;;)
	{
		AnjutaToken *next;

		if (child->parent == children->parent) child->parent = parent;
		if (child->group == children->group) child->group = parent->group;

		next = anjuta_token_next_child (child, &last);
		if (next == NULL) break;
		child = next;
	}

	child->next = parent->children;
	if (child->next) child->next->prev = child;
	parent->children = children;

	return children;
}
