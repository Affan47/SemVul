on_btn_title_clicked (GtkButton *button, GbemolApp* app)
{
	GbemolMpdSong *song = gbemol_mpd_get_current_song (app->mpd);

	if (!song->artist && song->name && (song->time == MPD_SONG_NO_TIME))
		return;
	gtk_notebook_set_current_page (GTK_NOTEBOOK (app->notebook), 2);
	gbemol_info_set_song (app->info, song);
	gbemol_mpd_free_song (song);
}
