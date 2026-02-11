gth_file_store_exec_remove (GthFileStore *file_store)
{
	GList *scan;

	if (file_store->priv->queue == NULL)
		return;

	file_store->priv->queue = g_list_reverse (file_store->priv->queue);
	for (scan = file_store->priv->queue; scan; scan = scan->next) {
		GthFileRow *row = scan->data;

		if (row->visible)
			_gth_file_store_hide_row (file_store, row);

		file_store->priv->all_rows[row->abs_pos] = NULL;
		_gth_file_row_unref (row);
	}
	_gth_file_store_compact_rows (file_store);
	_gth_file_store_clear_queue (file_store);

	_gth_file_store_update_visibility (file_store, NULL, -1);
}
