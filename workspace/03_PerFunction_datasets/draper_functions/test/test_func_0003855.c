play_cb(GtkWidget *widget, gpointer data)
{
	PlaylistWindow *playlist_window = (PlaylistWindow *)data;
	Playlist *pl = playlist_window->GetPlaylist();
	CorePlayer *p = pl->GetCorePlayer();
	if (p) {
		pl->UnPause();
		if (!pl->Length()) {
			eject_cb(widget, data);
		} else if (pl->Length()) {
			GDK_THREADS_LEAVE();
			pl->Play(pl->GetCurrent());
			GDK_THREADS_ENTER();
		}
	}
}
