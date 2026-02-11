table_subset_is_cell_editable (ETableModel *table_model,
                               gint col,
                               gint row)
{
	ETableSubset *table_subset = (ETableSubset *) table_model;

	g_return_val_if_fail (VALID_ROW (table_subset, row), FALSE);

	return e_table_model_is_cell_editable (
		table_subset->priv->source_model,
		col, MAP_ROW (table_subset, row));
}
