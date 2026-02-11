table_subset_proxy_model_row_changed (ETableModel *source_model,
                                      gint row,
                                      ETableSubset *table_subset)
{
	ETableSubsetClass *class;

	class = E_TABLE_SUBSET_GET_CLASS (table_subset);

	if (class->proxy_model_row_changed != NULL)
		class->proxy_model_row_changed (
			table_subset, source_model, row);
}
