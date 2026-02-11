totem_playlist_get_playing (TotemPlaylist *playlist)
{
	GtkTreeIter iter;
	TotemPlaylistStatus status;

	g_return_val_if_fail (TOTEM_IS_PLAYLIST (playlist), TOTEM_PLAYLIST_STATUS_NONE);

	if (gtk_tree_model_get_iter (playlist->priv->model, &iter, playlist->priv->current) == FALSE)
		return TOTEM_PLAYLIST_STATUS_NONE;

	gtk_tree_model_get (playlist->priv->model,
			    &iter,
			    PLAYING_COL, &status,
			    -1);

	return status;
}
