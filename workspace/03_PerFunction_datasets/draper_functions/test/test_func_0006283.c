sdb_model_iter_has_child (GtkTreeModel *tree_model,
                                GtkTreeIter *iter)
{
	gint offset;
	SymbolDBModelNode *node, *parent_node;

	g_return_val_if_fail (sdb_model_iter_is_valid (tree_model, iter),
	                      FALSE);

	parent_node = (SymbolDBModelNode*) iter->user_data;
	offset = GPOINTER_TO_INT (iter->user_data2);

	node = sdb_model_node_get_child (parent_node, offset);


	if (node == NULL)
		return FALSE;
	return sdb_model_get_has_child (SYMBOL_DB_MODEL (tree_model), node);
}
