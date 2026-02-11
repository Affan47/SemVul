brasero_playlist_try_again (BraseroPlaylist *playlist)
{
	if (!brasero_search_engine_is_available (playlist->priv->engine))
		return TRUE;

	brasero_playlist_search (playlist);

	playlist->priv->id = 0;
	return FALSE;
}
