tree_selection_model_select_all (ESelectionModel *selection)
{
	ETreeSelectionModel *etsm = E_TREE_SELECTION_MODEL (selection);
	ETreePath root;

	root = e_tree_model_get_root (etsm->priv->model);
	if (root == NULL)
		return;

	clear_selection (etsm);


	e_tree_model_node_traverse (
		etsm->priv->model, root,
		tree_selection_model_traverse_cb,
		selection);

	if (etsm->priv->cursor_path == NULL)
		etsm->priv->cursor_path = e_tree_table_adapter_node_at_row (
			etsm->priv->etta, 0);

	e_selection_model_selection_changed (E_SELECTION_MODEL (etsm));

	e_selection_model_cursor_changed (
		E_SELECTION_MODEL (etsm),
		get_cursor_row (etsm), etsm->priv->cursor_col);
}
