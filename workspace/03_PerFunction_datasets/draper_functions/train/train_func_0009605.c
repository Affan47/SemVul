explore_select_song ( song * s) {
    GtkTreeIter  * iter;
    GtkTreePath * path;
    if (s == NULL)
        return;
    iter = g_hash_table_lookup(name_iter_hash, s->path);
    if (iter) {
        path = gtk_tree_model_get_path(GTK_TREE_MODEL(store), iter);
        gtk_tree_view_expand_to_path(GTK_TREE_VIEW(tree_view), path);
        gtk_tree_selection_select_path(
            gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view)),
            path);

    }
}
