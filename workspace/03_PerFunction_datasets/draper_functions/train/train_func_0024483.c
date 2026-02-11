e_table_subset_construct (ETableSubset *table_subset,
                          ETableModel *source_model,
                          gint nvals)
{
	gulong handler_id;
	guint *buffer = NULL;
	gint i;

	if (nvals > 0)
		buffer = (guint *) g_malloc (sizeof (guint) * nvals);
	table_subset->map_table = (gint *) buffer;
	table_subset->n_map = nvals;
	table_subset->priv->source_model = g_object_ref (source_model);


	for (i = 0; i < nvals; i++)
		table_subset->map_table[i] = i;

	handler_id = g_signal_connect (
		source_model, "model_pre_change",
		G_CALLBACK (table_subset_proxy_model_pre_change),
		table_subset);
	table_subset->priv->table_model_pre_change_handler_id = handler_id;

	handler_id = g_signal_connect (
		source_model, "model_no_change",
		G_CALLBACK (table_subset_proxy_model_no_change),
		table_subset);
	table_subset->priv->table_model_no_change_handler_id = handler_id;

	handler_id = g_signal_connect (
		source_model, "model_changed",
		G_CALLBACK (table_subset_proxy_model_changed),
		table_subset);
	table_subset->priv->table_model_changed_handler_id = handler_id;

	handler_id = g_signal_connect (
		source_model, "model_row_changed",
		G_CALLBACK (table_subset_proxy_model_row_changed),
		table_subset);
	table_subset->priv->table_model_row_changed_handler_id = handler_id;

	handler_id = g_signal_connect (
		source_model, "model_cell_changed",
		G_CALLBACK (table_subset_proxy_model_cell_changed),
		table_subset);
	table_subset->priv->table_model_cell_changed_handler_id = handler_id;

	handler_id = g_signal_connect (
		source_model, "model_rows_inserted",
		G_CALLBACK (table_subset_proxy_model_rows_inserted),
		table_subset);
	table_subset->priv->table_model_rows_inserted_handler_id = handler_id;

	handler_id = g_signal_connect (
		source_model, "model_rows_deleted",
		G_CALLBACK (table_subset_proxy_model_rows_deleted),
		table_subset);
	table_subset->priv->table_model_rows_deleted_handler_id = handler_id;

	return E_TABLE_MODEL (table_subset);
}
