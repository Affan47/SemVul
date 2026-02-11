brasero_preview_set_uri_delayed_cb (gpointer data)
{
	BraseroPreview *self = BRASERO_PREVIEW (data);
	BraseroPreviewPrivate *priv;

	priv = BRASERO_PREVIEW_PRIVATE (self);

	brasero_player_set_uri (BRASERO_PLAYER (priv->player), priv->uri);
	if (priv->end >= 0 && priv->start >= 0)
		brasero_player_set_boundaries (BRASERO_PLAYER (priv->player),
					       priv->start,
					       priv->end);

	priv->set_uri_id = 0;
	return FALSE;
}
