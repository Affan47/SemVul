adjust_displayed_chunk (GdaDataProxy *proxy)
{
	g_return_if_fail (proxy->priv->model);

	gda_mutex_lock (proxy->priv->mutex);


	if (proxy->priv->chunk_sync_idle_id) {
		g_idle_remove_by_data (proxy);
		proxy->priv->chunk_sync_idle_id = 0;
	}


	if (proxy->priv->chunk_to) {
		display_chunk_free (proxy->priv->chunk_to);
		proxy->priv->chunk_to = NULL;
	}
	proxy->priv->chunk_to = compute_display_chunk (proxy);
	if (!proxy->priv->chunk_to) {
		gda_mutex_unlock (proxy->priv->mutex);
		return;
	}


	gboolean equal = FALSE;
	if (proxy->priv->chunk && proxy->priv->chunk_to->mapping) {

		if (proxy->priv->chunk->mapping->len == proxy->priv->chunk_to->mapping->len) {
			gsize i;
			equal = TRUE;
			for (i = 0; i < proxy->priv->chunk->mapping->len; i++) {
				if (g_array_index (proxy->priv->chunk->mapping, gint, i) !=
				    g_array_index (proxy->priv->chunk_to->mapping, gint, i)) {
					equal = FALSE;
					break;
				}
			}
		}
	}
	else if (!proxy->priv->chunk && !proxy->priv->chunk_to->mapping)
		equal = TRUE;


	if (! equal) {
#ifdef DEBUG_SYNC
		g_print ("////////// %s(%d)\n", __FUNCTION__, __LINE__);
#endif
		display_chunks_dump (proxy);

		g_signal_emit (G_OBJECT (proxy),
                               gda_data_proxy_signals[SAMPLE_CHANGED],
                               0, proxy->priv->sample_first_row, proxy->priv->sample_last_row);


		proxy->priv->chunk_sep = 0;
		proxy->priv->chunk_proxy_nb_rows = -1;
		if (!proxy->priv->defer_sync)
			chunk_sync_idle (proxy);
		else
			proxy->priv->chunk_sync_idle_id = g_idle_add ((GSourceFunc) chunk_sync_idle, proxy);
	}
	else {

		if (proxy->priv->chunk_to) {
			display_chunk_free (proxy->priv->chunk_to);
			proxy->priv->chunk_to = NULL;
		}
	}

	gda_mutex_unlock (proxy->priv->mutex);
}
