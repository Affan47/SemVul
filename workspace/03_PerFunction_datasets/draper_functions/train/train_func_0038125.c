e_tree_table_adapter_node_set_expanded (ETreeTableAdapter *etta,
                                        ETreePath path,
                                        gboolean expanded)
{
	GNode *gnode;
	node_t *node;
	gint row;

	g_return_if_fail (E_IS_TREE_TABLE_ADAPTER (etta));

	gnode = lookup_gnode (etta, path);

	if (!expanded && (!gnode || (e_tree_model_node_is_root (etta->priv->source_model, path) && !etta->priv->root_visible)))
		return;

	if (!gnode && expanded) {
		ETreePath parent = e_tree_model_node_get_parent (etta->priv->source_model, path);
		g_return_if_fail (parent != NULL);
		e_tree_table_adapter_node_set_expanded (etta, parent, expanded);
		gnode = lookup_gnode (etta, path);
	}
	g_return_if_fail (gnode != NULL);

	node = (node_t *) gnode->data;

	if (expanded == node->expanded)
		return;

	node->expanded = expanded;

	row = e_tree_table_adapter_row_of_node (etta, path);
	if (row == -1)
		return;

	e_table_model_pre_change (E_TABLE_MODEL (etta));
	e_table_model_pre_change (E_TABLE_MODEL (etta));
	e_table_model_row_changed (E_TABLE_MODEL (etta), row);

	if (expanded) {
		gint num_children = insert_children (etta, gnode);
		update_child_counts (gnode, num_children);
		if (etta->priv->sort_info && e_table_sort_info_sorting_get_count (etta->priv->sort_info) > 0)
			resort_node (etta, gnode, TRUE);
		resize_map (etta, etta->priv->n_map + num_children);
		move_map_elements (etta, row + 1 + num_children, row + 1, etta->priv->n_map - row - 1 - num_children);
		fill_map (etta, row, gnode);
		if (num_children != 0) {
			e_table_model_rows_inserted (E_TABLE_MODEL (etta), row + 1, num_children);
		} else
			e_table_model_no_change (E_TABLE_MODEL (etta));
	} else {
		gint num_children = delete_children (etta, gnode);
		if (num_children == 0) {
			e_table_model_no_change (E_TABLE_MODEL (etta));
			return;
		}
		move_map_elements (etta, row + 1, row + 1 + num_children, etta->priv->n_map - row - 1 - num_children);
		update_child_counts (gnode, - num_children);
		resize_map (etta, etta->priv->n_map - num_children);
		e_table_model_rows_deleted (E_TABLE_MODEL (etta), row + 1, num_children);
	}
}
