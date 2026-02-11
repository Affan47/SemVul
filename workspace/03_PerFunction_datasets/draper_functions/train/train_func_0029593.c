snippets_db_iter_parent (GtkTreeModel *tree_model,
                         GtkTreeIter *iter,
                         GtkTreeIter *child)
{

	g_return_val_if_fail (ANJUTA_IS_SNIPPETS_DB (tree_model), FALSE);
	g_return_val_if_fail (child != NULL, FALSE);


	if (iter_is_snippets_group_node (child))
		return FALSE;


	iter->user_data  = child->user_data2;
	iter->user_data2 = NULL;
	iter->stamp      = child->stamp;

	return TRUE;
}
