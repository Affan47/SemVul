hybrid_blist_select_first_item(HybridAccount *account)
{
    GtkTreeModel     *model;
    GtkTreeSelection *selection;
    GHashTableIter    hash_iter;
    HybridGroup      *group;
    gpointer          key;

    g_return_if_fail(account != NULL);

    model = gtk_tree_view_get_model(GTK_TREE_VIEW(blist->treeview));

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(blist->treeview));

#if 0
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
        return;
    }
#endif

    g_hash_table_iter_init(&hash_iter, account->group_list);

    if (!g_hash_table_iter_next(&hash_iter, &key, (gpointer*)&group)) {
        return;
    }

    current_choose_account = group->account;

    gtk_tree_selection_select_iter(selection, &group->iter);

    if (current_choose_path) {
        gtk_tree_path_free(current_choose_path);
    }

    current_choose_path = gtk_tree_model_get_path(model, &group->iter);
}
