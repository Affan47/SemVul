gth_file_list_finalize (GObject *object)
{
	GthFileList *file_list;

	file_list = GTH_FILE_LIST (object);

	if (file_list->priv != NULL) {
		_gth_file_list_clear_queue (file_list);
		_g_object_unref (file_list->priv->thumb_loader);
		_g_object_list_unref (file_list->priv->visibles);
		g_hash_table_unref (file_list->priv->thumb_data);
		if (file_list->priv->icon_cache != NULL)
			gth_icon_cache_free (file_list->priv->icon_cache);
		g_object_unref (file_list->priv->settings);

		g_free (file_list->priv);
		file_list->priv = NULL;
	}

	G_OBJECT_CLASS (gth_file_list_parent_class)->finalize (object);
}
