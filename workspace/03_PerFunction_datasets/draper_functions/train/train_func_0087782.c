gth_file_store_exec_set (GthFileStore *file_store)
{


	if (file_store->priv->update_filter)
		_gth_file_store_list_changed (file_store);
	else
		_gth_file_store_thumbnails_changed (file_store);

	_gth_file_store_clear_queue (file_store);

	if (file_store->priv->update_filter) {
		_gth_file_store_update_visibility (file_store, NULL, -1);
		file_store->priv->update_filter = FALSE;
	}
}
