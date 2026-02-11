gimmix_update_global_song_info (void)
{
	mpd_Song *tsi = NULL;

	tsi = mpd_playlist_get_current_song (gmo);
	if (tsi!=NULL)
	{
		glob_song_info = tsi;
	}

	return;
}
