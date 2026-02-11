tm_delete_track(GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, gpointer data) {
    Track *track;

    gtk_tree_model_get(model, iter, READOUT_COL, &track, -1);

    if (track == (Track *) data) {
        GtkTreeIter temp;

        GtkTreeSelection *selection = gtk_tree_view_get_selection(track_treeview);

        gtk_tree_selection_unselect_iter(selection, iter);


        convert_iter(model, iter, &temp);
        gtk_list_store_remove(get_model_as_store(model), &temp);

        return TRUE;
    }
    return FALSE;
}
