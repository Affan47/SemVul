gnc_tree_model_budget_get_iter_for_budget(GtkTreeModel *tm, GtkTreeIter *iter,
        GncBudget *bgt)
{
    GValue gv = { 0 };
    const GncGUID *guid1;
    GncGUID *guid2;

    g_return_val_if_fail(GNC_BUDGET(bgt), FALSE);

    guid1 = gnc_budget_get_guid(bgt);
    if (!gtk_tree_model_get_iter_first(tm, iter))
        return FALSE;
    while (gtk_list_store_iter_is_valid(GTK_LIST_STORE(tm), iter))
    {
        gtk_tree_model_get_value(tm, iter, BUDGET_GUID_COLUMN, &gv);
        guid2 = (GncGUID *) g_value_get_pointer(&gv);
        g_value_unset(&gv);

        if (guid_equal(guid1, guid2))
            return TRUE;

        if (!gtk_tree_model_iter_next(tm, iter))
            return FALSE;
    }
    return FALSE;
}
