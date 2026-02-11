gnc_tree_view_account_add_kvp_column (GncTreeViewAccount *view,
                                      const gchar *column_title,
                                      const gchar *kvp_key)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    g_return_val_if_fail (GNC_IS_TREE_VIEW_ACCOUNT (view), NULL);
    g_return_val_if_fail (kvp_key != NULL, NULL);

    column = gnc_tree_view_add_text_column(GNC_TREE_VIEW(view), column_title,
                                           kvp_key, NULL, "Sample text",
                                           -1, -1, NULL);


    renderer = gnc_tree_view_column_get_renderer(column);
    g_object_set (G_OBJECT (renderer), "xalign", 1.0, NULL);

    gtk_tree_view_column_set_cell_data_func (column, renderer,
            account_cell_kvp_data_func,
            g_strdup(kvp_key), g_free);
    return column;
}
