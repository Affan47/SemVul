gwy_null_store_row_changed(GwyNullStore *store,
                           guint i)
{
    GtkTreePath *path;
    GtkTreeIter iter;

    g_return_if_fail(GWY_IS_NULL_STORE(store));
    g_return_if_fail(i < store->n);

    iter.stamp = store->stamp;
    iter.user_data = GUINT_TO_POINTER(i);

    path = gtk_tree_path_new();
    gtk_tree_path_append_index(path, i);
    gtk_tree_model_row_changed(GTK_TREE_MODEL(store), path, &iter);
    gtk_tree_path_free(path);
}
