et_search_search (ETableSearch *search,
                  gchar *string,
                  ETableSearchFlags flags,
                  ETree *tree)
{
	ETreePath cursor;
	ETreePath found;
	SearchSearchStruct cb_data;
	ETableCol *col = current_search_col (tree);

	if (col == NULL)
		return FALSE;

	cb_data.tree = tree;
	cb_data.string = string;

	cursor = e_tree_get_cursor (tree);

	if (cursor && (flags & E_TABLE_SEARCH_FLAGS_CHECK_CURSOR_FIRST)) {
		gconstpointer value;

		value = e_tree_model_value_at (
			tree->priv->model, cursor, col->spec->model_col);

		if (col->search (value, string)) {
			return TRUE;
		}
	}

	found = e_tree_model_node_find (
		tree->priv->model, cursor, NULL,
		search_search_callback, &cb_data);
	if (found == NULL)
		found = e_tree_model_node_find (
			tree->priv->model, NULL, cursor,
			search_search_callback, &cb_data);

	if (found && found != cursor) {
		gint model_row;

		e_tree_table_adapter_show_node (tree->priv->etta, found);
		model_row = e_tree_table_adapter_row_of_node (tree->priv->etta, found);

		e_selection_model_select_as_key_press (
			E_SELECTION_MODEL (tree->priv->selection),
			model_row, col->spec->model_col,
			GDK_CONTROL_MASK);
		return TRUE;
	} else if (cursor && !(flags & E_TABLE_SEARCH_FLAGS_CHECK_CURSOR_FIRST)) {
		gconstpointer value;

		value = e_tree_model_value_at (
			tree->priv->model, cursor, col->spec->model_col);

		return col->search (value, string);
	} else
		return FALSE;
}
