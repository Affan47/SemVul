sdb_model_iter_nth_child (GtkTreeModel *tree_model,
                          GtkTreeIter *iter,
                          GtkTreeIter *parent,
                          gint n)
{
	SymbolDBModelNode *node;

	g_return_val_if_fail (SYMBOL_DB_IS_MODEL(tree_model), FALSE);
	g_return_val_if_fail (iter != NULL, FALSE);
	g_return_val_if_fail (n >= 0, FALSE);

	if (!sdb_model_iter_children (tree_model, iter, parent))
		return FALSE;

	node = (SymbolDBModelNode*) (iter->user_data);

	g_return_val_if_fail (n < node->n_children, FALSE);

	iter->user_data2 = GINT_TO_POINTER (n);

	g_assert (sdb_model_iter_is_valid (tree_model, iter));

	return TRUE;
}
