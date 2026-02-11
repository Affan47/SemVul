gnc_reconcile_view_line_toggled (GNCQueryView *qview,
                                 gpointer item,
                                 gpointer user_data)
{
    GNCReconcileView *view;
    GtkTreeModel     *model;
    GtkTreeIter       iter;
    gpointer          entry;

    g_return_if_fail (user_data);
    g_return_if_fail (GNC_IS_QUERY_VIEW (qview));

    view = user_data;

    model = gtk_tree_view_get_model (GTK_TREE_VIEW (qview));
    gtk_tree_model_iter_nth_child (model, &iter, NULL, qview->toggled_row);
    gtk_list_store_set (GTK_LIST_STORE (model), &iter, qview->toggled_column, GPOINTER_TO_INT(item), -1);
    gtk_tree_model_get (model, &iter, 0, &entry, -1);

    gnc_reconcile_view_toggle (view, entry);
}
