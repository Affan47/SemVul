sdb_model_node_cleanse (SymbolDBModelNode *node, gboolean force)
{
	SymbolDBModelPage *page, *next;
	gint i;

	g_return_val_if_fail (node != NULL, FALSE);


	if (!force)
	{
		g_return_val_if_fail (node->children_ref_count == 0, FALSE);
	}

	if (node->children)
	{


		for (i = 0; i < node->n_children; i++)
		{
			SymbolDBModelNode *child = sdb_model_node_get_child (node, i);
			if (child)
			{
				if (!force)
				{

					g_warn_if_fail (child->children_ref_count == 0);
				}
				sdb_model_node_free (child, force);
				sdb_model_node_set_child (node, i, NULL);
			}
		}
	}


	page = node->pages;
	while (page)
	{
		next = page->next;
		g_slice_free (SymbolDBModelPage, page);
		page = next;
	}
	node->pages = NULL;
	node->children_ensured = FALSE;
	node->n_children = 0;


	g_free (node->children);
	node->children = NULL;

	return TRUE;
}
