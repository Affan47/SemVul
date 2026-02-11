tm_track_changed(Track *track) {
    GtkTreeModel *model = gtk_tree_view_get_model(track_treeview);
    if (model != NULL)
        gtk_tree_model_foreach(model, tm_model_track_changed, track);
}
