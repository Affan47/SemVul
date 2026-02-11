on_mpd_playlist_changed_cb (GbemolMpd* mpd, GbemolApp* app)
{
	if (!gbemol_mpd_is_connected (mpd) || (mpd->status == NULL))
		return;

	if (gbemol_playlist_current_is_selected (app->pls))
	{
		gbemol_playlist_update_songs (app->pls);
			if (app->mpd->status != NULL && app->mpd->status->songid != -1)
				gbemol_playlist_bold_song (app->pls, app->mpd->status->songid);
	}
}
