brasero_player_bacon_set_uri (BraseroPlayerBacon *bacon, const gchar *uri)
{
	if (bacon->priv->uri) {
		g_free (bacon->priv->uri);
		bacon->priv->uri = NULL;
	}

	if (uri) {
		bacon->priv->uri = g_strdup (uri);

		gst_element_set_state (bacon->priv->pipe, GST_STATE_NULL);
		bacon->priv->state = GST_STATE_NULL;

		g_object_set (G_OBJECT (bacon->priv->pipe),
			      "uri", uri,
			      NULL);

		gst_element_set_state (bacon->priv->pipe, GST_STATE_PAUSED);
	}
	else if (bacon->priv->pipe)
		gst_element_set_state (bacon->priv->pipe, GST_STATE_NULL);
}
