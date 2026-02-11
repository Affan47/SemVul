check_toggled (GtkCellRendererToggle *cellrenderertoggle, gchar *path, GtkTreeView *view)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    model = gtk_tree_view_get_model (view);
    g_return_if_fail (CRYPTUI_IS_KEY_STORE (model));

    g_assert (path != NULL);

    if (gtk_tree_model_get_iter_from_string (model, &iter, path))
        cryptui_key_store_check_toggled (CRYPTUI_KEY_STORE (model), view, &iter);
}
