pm_select_playlist(Playlist *playlist) {
    GtkTreeIter iter;
    GtkTreeSelection *ts;

    g_return_if_fail (playlist_treeview);

    if (!playlist) {
        ts = gtk_tree_view_get_selection(playlist_treeview);
        gtk_tree_selection_unselect_all(ts);
    }
    else if (pm_get_iter_for_playlist(playlist, &iter)) {
        ts = gtk_tree_view_get_selection(playlist_treeview);
        gtk_tree_selection_select_iter(ts, &iter);
    }

    if (gtkpod_get_current_playlist() != playlist) {
        gtkpod_set_current_playlist(playlist);
    }
}
