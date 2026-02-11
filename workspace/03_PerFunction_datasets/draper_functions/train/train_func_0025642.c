do_list_store(void)
{
    GtkTreeModel *model;
    GtkWidget *treeview;

    model = create_model();
    if (!model)
        return NULL;

    treeview = gtk_tree_view_new_with_model(model);
    g_object_unref(model);
    gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(treeview), TRUE);
    gtk_tree_view_set_search_column(GTK_TREE_VIEW(treeview), COLUMN_NICK);


    add_columns(GTK_TREE_VIEW(treeview));

    return treeview;
}
