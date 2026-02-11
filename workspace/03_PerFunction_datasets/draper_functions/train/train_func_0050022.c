playlist3_insert_browser(GtkTreeIter * iter, gint position)
{
    GtkTreeIter it, *sib = NULL;
    gint pos = 0;
    GtkTreeModel *model = GTK_TREE_MODEL(pl3_tree);
    if (gtk_tree_model_get_iter_first(model, &it))
    {
        do
        {
            gtk_tree_model_get(model, &it, PL3_CAT_ORDER, &pos, -1);
            if (position <= pos)
                sib = &it;
        } while (sib == NULL && gtk_tree_model_iter_next(model, &it));
    }
    gtk_list_store_insert_before(GTK_LIST_STORE(pl3_tree), iter, sib);
    gtk_list_store_set(GTK_LIST_STORE(pl3_tree), iter, PL3_CAT_ORDER, position, -1);
}
