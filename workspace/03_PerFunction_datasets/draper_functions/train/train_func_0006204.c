pm_drag_data_delete_remove_playlist(GtkTreeModel *tm, GtkTreePath *tp, GtkTreeIter *iter, gpointer data) {
    Playlist *pl;
    g_return_if_fail (tm);
    g_return_if_fail (iter);
    gtk_tree_model_get(tm, iter, PM_COLUMN_PLAYLIST, &pl, -1);
    g_return_if_fail (pl);
    gp_playlist_remove(pl);
}
