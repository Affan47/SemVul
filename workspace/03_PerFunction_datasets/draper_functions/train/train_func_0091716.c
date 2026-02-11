del_directory(struct w *widgets)
{


    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    GtkTreePath *path;
    gint has_row_above;
    gboolean val;

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widgets->directory_treeview));

    val = gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);

    path = gtk_tree_model_get_path(GTK_TREE_MODEL(model), &iter);

    has_row_above = gtk_tree_path_prev(path);


    if( val && has_row_above )
      gtk_list_store_remove(widgets->directory_store, &iter);

    gtk_tree_path_free(path);
}
