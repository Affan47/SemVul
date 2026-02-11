sdb_model_get_value (GtkTreeModel *tree_model,
                     GtkTreeIter *iter, gint column,
                     GValue *value)
{
	SymbolDBModelPriv *priv;
	SymbolDBModelNode *parent_node, *node;
	gint offset;

	g_return_if_fail (sdb_model_iter_is_valid (tree_model, iter));

	priv = SYMBOL_DB_MODEL (tree_model)->priv;

	g_return_if_fail (column >= 0);
	g_return_if_fail (column < priv->n_columns);

	parent_node = (SymbolDBModelNode*) iter->user_data;
	offset = GPOINTER_TO_INT (iter->user_data2);

	if (sdb_model_node_get_child (parent_node, offset) == NULL)
		sdb_model_page_fault (SYMBOL_DB_MODEL (tree_model),
		                      parent_node, offset);
	node = sdb_model_node_get_child (parent_node, offset);
	g_value_init (value, priv->column_types[column]);

	if (node == NULL)
		return;


	if (!node->has_child_ensured)
	{
		sdb_model_get_has_child (SYMBOL_DB_MODEL (tree_model), node);
	}
	g_value_copy (&(node->values[column]), value);
}
