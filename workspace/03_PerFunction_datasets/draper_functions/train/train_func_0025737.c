get_selected_entry (void)
{
    g_return_val_if_fail (treeview && search_matches, -1);

    GtkTreeModel * model = gtk_tree_view_get_model ((GtkTreeView *) treeview);
    GtkTreeSelection * selection = gtk_tree_view_get_selection ((GtkTreeView *) treeview);
    GtkTreeIter iter;

    if (! gtk_tree_selection_get_selected (selection, NULL, & iter))
        return -1;

    GtkTreePath * path = gtk_tree_model_get_path (model, & iter);
    int row = gtk_tree_path_get_indices (path)[0];
    gtk_tree_path_free (path);

    g_return_val_if_fail (row >= 0 && row < search_matches->len, -1);
    return g_array_index (search_matches, int, row);
}
