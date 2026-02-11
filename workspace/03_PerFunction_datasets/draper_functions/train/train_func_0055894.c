RemoveSelectedFromTree(GtkWidget *widget)
{
    GList *list;
    GtkTreeSelection *TreeSel;
    GtkTreePath *path;
    GtkTreeModel *model;
    gchar *str_data;
    gboolean valid = 0;
    GtkTreeIter iter;

    model = gtk_tree_view_get_model(GTK_TREE_VIEW(widget));
    TreeSel = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
    list = gtk_tree_selection_get_selected_rows(TreeSel,NULL);
    if(!list)
        return;
    while(list) {
        gtk_tree_model_get_iter(GTK_TREE_MODEL(model), &iter,
                                (GtkTreePath *)g_list_nth(list, 0)->data);
        gtk_list_store_set(GTK_LIST_STORE(model), &iter, 2,"delete", -1);
        list = g_list_next(list);
    }
    g_list_free(list);
    valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(model), &iter);
    path = gtk_tree_model_get_path(GTK_TREE_MODEL(model), &iter);
    while(valid) {
        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter,2,&str_data,-1);
        if(!g_strcmp0(str_data,"delete"))
            gtk_list_store_remove(GTK_LIST_STORE(model),&iter);
        else
            gtk_tree_path_next(path);
        valid = gtk_tree_model_get_iter(GTK_TREE_MODEL(model), &iter, path);
    }
}
