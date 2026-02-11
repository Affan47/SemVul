gwy_null_store_get_tree_iter(GtkTreeModel *model,
                             GtkTreeIter *iter,
                             GtkTreePath *path)
{
    GwyNullStore *store;
    guint i;

    g_return_val_if_fail(gtk_tree_path_get_depth(path) > 0, FALSE);
    store = GWY_NULL_STORE(model);

    i = gtk_tree_path_get_indices(path)[0];
    if (i >= store->n)
        return FALSE;


    iter->stamp = store->stamp;
    iter->user_data = GUINT_TO_POINTER(i);

    return TRUE;
}
