brasero_checksum_image_stop (BraseroJob *job,
			     GError **error)
{
	BraseroChecksumImagePrivate *priv;

	priv = BRASERO_CHECKSUM_IMAGE_PRIVATE (job);

	g_mutex_lock (priv->mutex);
	if (priv->thread) {
		priv->cancel = 1;
		g_cond_wait (priv->cond, priv->mutex);
		priv->cancel = 0;
		priv->thread = NULL;
	}
	g_mutex_unlock (priv->mutex);

	if (priv->end_id) {
		g_source_remove (priv->end_id);
		priv->end_id = 0;
	}

	if (priv->checksum) {
		g_checksum_free (priv->checksum);
		priv->checksum = NULL;
	}

	return BRASERO_BURN_OK;
}
