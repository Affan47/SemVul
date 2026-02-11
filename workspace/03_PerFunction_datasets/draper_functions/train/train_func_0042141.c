et_table_rows_deleted (ETableModel *table_model,
                       gint row,
                       gint count,
                       ETree *tree)
{
	ETreeTableAdapter *adapter;
	ETreePath * node, * prev_node;


	if (e_selection_model_cursor_row (tree->priv->selection) >= 0
			|| row == 0)
		return;

	adapter = e_tree_get_table_adapter (tree);
	prev_node = e_tree_table_adapter_node_at_row (adapter, row - 1);
	node = e_tree_get_cursor (tree);


	while (node) {
		node = e_tree_model_node_get_parent (tree->priv->model, node);
		if (node == prev_node) {

			e_tree_set_cursor (tree, prev_node);
			return;
		}
	}
}
