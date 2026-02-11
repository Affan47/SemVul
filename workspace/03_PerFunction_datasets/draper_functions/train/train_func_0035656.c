clean_proxy (GdaDataProxy *proxy)
{
	if (proxy->priv->all_modifs) {
		gda_data_proxy_cancel_all_changes (proxy);
		g_assert (! proxy->priv->all_modifs);
	}

	if (proxy->priv->modify_rows) {
		g_hash_table_destroy (proxy->priv->modify_rows);
		proxy->priv->modify_rows = NULL;
	}

	if (proxy->priv->filter_vcnc) {
		g_object_unref (proxy->priv->filter_vcnc);
		proxy->priv->filter_vcnc = NULL;
	}

	if (proxy->priv->filter_expr) {
		g_free (proxy->priv->filter_expr);
		proxy->priv->filter_expr = NULL;
	}

	if (proxy->priv->filter_stmt) {
		g_object_unref (proxy->priv->filter_stmt);
		proxy->priv->filter_stmt = NULL;
	}

	if (proxy->priv->filtered_rows) {
		g_object_unref (proxy->priv->filtered_rows);
		proxy->priv->filtered_rows = NULL;
	}

	proxy->priv->force_direct_mapping = FALSE;
	if (proxy->priv->chunk_sync_idle_id) {
		g_idle_remove_by_data (proxy);
		proxy->priv->chunk_sync_idle_id = 0;
	}

	if (proxy->priv->chunk) {
		display_chunk_free (proxy->priv->chunk);
		proxy->priv->chunk = NULL;
	}
	if (proxy->priv->chunk_to) {
		display_chunk_free (proxy->priv->chunk_to);
		proxy->priv->chunk_to = NULL;
	}

	if (proxy->priv->columns) {
		gint i;
		for (i = 0; i < 2 * proxy->priv->model_nb_cols; i++)
			g_object_unref (G_OBJECT (proxy->priv->columns[i]));
		g_free (proxy->priv->columns);
		proxy->priv->columns = NULL;
	}

	if (proxy->priv->model) {
		g_signal_handlers_disconnect_by_func (G_OBJECT (proxy->priv->model),
						      G_CALLBACK (proxied_model_row_inserted_cb), proxy);
		g_signal_handlers_disconnect_by_func (G_OBJECT (proxy->priv->model),
						      G_CALLBACK (proxied_model_row_updated_cb), proxy);
		g_signal_handlers_disconnect_by_func (G_OBJECT (proxy->priv->model),
						      G_CALLBACK (proxied_model_row_removed_cb), proxy);
		g_signal_handlers_disconnect_by_func (G_OBJECT (proxy->priv->model),
						      G_CALLBACK (proxied_model_reset_cb), proxy);
		g_signal_handlers_disconnect_by_func (G_OBJECT (proxy->priv->model),
						      G_CALLBACK (proxied_model_access_changed_cb), proxy);
		g_object_unref (proxy->priv->model);
		proxy->priv->model = NULL;
	}

	if (proxy->priv->columns_attrs) {
		g_free (proxy->priv->columns_attrs);
		proxy->priv->columns_attrs = NULL;
	}
}
