anjuta_token_insert_before (AnjutaToken *sibling, AnjutaToken *list)
{
	AnjutaToken *last;
	AnjutaToken *token;
	AnjutaToken *old_group;
	AnjutaToken *old_parent;

	g_return_val_if_fail (sibling != NULL, NULL);
	g_return_val_if_fail (list != NULL, NULL);

	old_group = list->group;
	old_parent = list->parent;


	for (token = list;;)
	{
		if (token->parent == old_parent) token->parent = sibling->parent;
		if (token->group == old_group) token->group = sibling->group;

		if (token->children != NULL)
		{
			token = token->children;
		}
		else if (token->next != NULL)
		{
			token = token->next;
		}
		else
		{
			while (token->parent != sibling->parent)
			{
				token = token->parent;
				if (token->next != NULL) break;
			}
			if (token->next == NULL) break;
			token = token->next;
		}
	}

	for (last = sibling; last->last != NULL; last = last->last);

	token->next = sibling;
	list->prev = sibling->prev;
	sibling->prev = token;

	if (list->prev) list->prev->next = list;

	if ((list->parent != NULL) && (list->parent->children == sibling)) list->parent->children = list;

	return list;
}
