e_tree_get_state_object (ETree *tree)
{
	ETableState *state;
	GPtrArray *columns;
	gint full_col_count;
	gint i, j;

	columns = e_table_specification_ref_columns (tree->priv->spec);

	state = e_table_state_new (tree->priv->spec);

	g_clear_object (&state->sort_info);
	if (tree->priv->sort_info != NULL)
		state->sort_info = g_object_ref (tree->priv->sort_info);

	state->col_count = e_table_header_count (tree->priv->header);
	full_col_count = e_table_header_count (tree->priv->full_header);

	state->column_specs = g_new (
		ETableColumnSpecification *, state->col_count);
	state->expansions = g_new (gdouble, state->col_count);

	for (i = 0; i < state->col_count; i++) {
		ETableCol *col = e_table_header_get_column (tree->priv->header, i);
		state->column_specs[i] = NULL;
		for (j = 0; j < full_col_count; j++) {
			if (col->spec->model_col == e_table_header_index (tree->priv->full_header, j)) {
				state->column_specs[i] =
					g_object_ref (columns->pdata[j]);
				break;
			}
		}
		state->expansions[i] = col->expansion;
	}

	g_ptr_array_unref (columns);

	return state;
}
