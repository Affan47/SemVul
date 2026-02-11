brasero_metadata_thumbnail (BraseroMetadata *self)
{
	BraseroMetadataPrivate *priv;
	gint64 position;
	gboolean res;

	priv = BRASERO_METADATA_PRIVATE (self);


	position = 15 * GST_SECOND;
	while (position > 0 && position >= priv->info->len)
		position -= 5 * GST_SECOND;

	if (position <= 0)
		return FALSE;

	gst_element_set_state (priv->pipeline, GST_STATE_PAUSED);

	priv->snapshot_started = 1;
	if (position < GST_SECOND)
		position = GST_SECOND;

	res = gst_element_seek_simple (priv->pipeline,
				       GST_FORMAT_TIME,
				       GST_SEEK_FLAG_FLUSH,
				       position);

	BRASERO_UTILS_LOG ("Seeking forward %i for %s", res, priv->info->uri);
	if (!res)
		return brasero_metadata_completed (self);

	g_object_set (priv->snapshot,
		      "send-messages", TRUE,
		      NULL);

	return TRUE;
}
