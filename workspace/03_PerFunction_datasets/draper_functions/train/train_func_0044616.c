brasero_metadata_get_info_async (BraseroMetadata *self,
				 const gchar *uri,
				 BraseroMetadataFlag flags)
{
	BraseroMetadataPrivate *priv;
	GstStateChangeReturn state_change;

	priv = BRASERO_METADATA_PRIVATE (self);

	priv->flags = flags;

	if (!brasero_metadata_set_new_uri (self, uri)) {
		g_object_ref (self);
		g_signal_emit (G_OBJECT (self),
			       brasero_metadata_signals [COMPLETED_SIGNAL],
			       0,
			       priv->error);
		g_object_unref (self);

		if (priv->error) {
			BRASERO_UTILS_LOG ("Failed to set new URI %s", priv->error->message);
			g_error_free (priv->error);
			priv->error = NULL;
		}
		return FALSE;
	}

	state_change = gst_element_set_state (GST_ELEMENT (priv->pipeline),
					      BRASERO_METADATA_INITIAL_STATE);

	priv->started = (state_change != GST_STATE_CHANGE_FAILURE);
	return priv->started;
}
