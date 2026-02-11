tm_select_current_position(gint x, gint y) {
    if (track_treeview) {
        GtkTreePath *path;

        gtk_tree_view_get_path_at_pos(track_treeview, x, y, &path, NULL, NULL, NULL);
        if (path) {
            GtkTreeSelection *ts = gtk_tree_view_get_selection(track_treeview);
            gtk_tree_selection_select_path(ts, path);
            gtk_tree_path_free(path);
        }
    }
}
