podcast_track__addlist_cb(gpointer data) {

        GtkTreeIter iter_track;
	playlist_t * pl = playlist_get_current();

        if (gtk_tree_selection_get_selected(music_select, NULL, &iter_track)) {
		podcast_track_addlist_iter(iter_track, pl, NULL, (GtkTreeIter *)data, 0);
		if (pl == playlist_get_current()) {
			playlist_content_changed(pl);
		}
		store_podcast_save();
	}
}
