pm_remove_playlist(Playlist *playlist) {
    GtkTreeModel *model;
    GtkTreeIter iter;

    g_return_if_fail (playlist);
    model = gtk_tree_view_get_model(playlist_treeview);
    g_return_if_fail (model);

    gtkpod_set_current_playlist(NULL);

    if (pm_get_iter_for_playlist(playlist, &iter)) {
        gtk_tree_store_remove(GTK_TREE_STORE (model), &iter);
    }
}
