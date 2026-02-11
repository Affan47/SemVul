gnc_tree_view_account_get_path_from_account (GncTreeViewAccount *view,
        Account *account)
{
    GtkTreeModel *model, *f_model, *s_model;
    GtkTreePath *path, *f_path, *s_path;

    ENTER("view %p, account %p (%s)", view, account, xaccAccountGetName(account));

    if (account == NULL)
    {
        LEAVE("no account");
        return NULL;
    }


    s_model = gtk_tree_view_get_model(GTK_TREE_VIEW(view));
    f_model = gtk_tree_model_sort_get_model(GTK_TREE_MODEL_SORT(s_model));
    model = gtk_tree_model_filter_get_model(GTK_TREE_MODEL_FILTER(f_model));
    path = gnc_tree_model_account_get_path_from_account (GNC_TREE_MODEL_ACCOUNT(model), account);
    if (path == NULL)
    {
        LEAVE("no path");
        return NULL;
    }


    f_path = gtk_tree_model_filter_convert_child_path_to_path (GTK_TREE_MODEL_FILTER (f_model), path);
    gtk_tree_path_free(path);
    if (!f_path)
    {
        LEAVE("no filter path");
        return NULL;
    }


    s_path = gtk_tree_model_sort_convert_child_path_to_path (GTK_TREE_MODEL_SORT (s_model), f_path);
    gtk_tree_path_free(f_path);
    debug_path(LEAVE, s_path);
    return s_path;
}
