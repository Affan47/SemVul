update_cb (void * data, void * user)
{
    g_return_if_fail (treeview);

    GtkTreeModel * model;
    GtkTreeIter iter;
    GtkTreePath * path = NULL;

    if (GPOINTER_TO_INT (data) <= PLAYLIST_UPDATE_SELECTION)
        return;

    if (cache != NULL)
    {
        ui_jump_to_track_cache_free (cache);
        cache = NULL;
    }


    if (GPOINTER_TO_INT (data) <= PLAYLIST_UPDATE_METADATA &&
     gtk_tree_selection_get_selected (gtk_tree_view_get_selection
     ((GtkTreeView *) treeview), & model, & iter))
        path = gtk_tree_model_get_path (model, & iter);

    fill_list ();

    if (path != NULL)
    {
        gtk_tree_selection_select_path (gtk_tree_view_get_selection
         ((GtkTreeView *) treeview), path);
        gtk_tree_view_scroll_to_cell ((GtkTreeView *) treeview, path, NULL, TRUE, 0.5, 0);
        gtk_tree_path_free (path);
    }
}
