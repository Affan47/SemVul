DeleteFiles(GData **widset)
{
        GtkWidget *widget;
        GtkTreeSelection *selection;
        GtkTreeModel *model;
        GtkTreeIter iter;

        widget = GTK_WIDGET(g_datalist_get_data(widset, "file-treeview-widget"));
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
        model = gtk_tree_view_get_model(GTK_TREE_VIEW(widget));
        if (!gtk_tree_model_get_iter_first(model, &iter))
                return;
        do {
mark:           if (gtk_tree_selection_iter_is_selected(selection, &iter)) {
                        if (gtk_list_store_remove(GTK_LIST_STORE(model), &iter))
                                goto mark;
                        break;
                }
        } while (gtk_tree_model_iter_next(model, &iter));
}
