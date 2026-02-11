GetRelList(RowSet * pRow)
{
    unsigned int i, j;
    GtkListStore *store;
    GType *types;
    GtkTreeIter iter;
    GtkCellRenderer *renderer;
    GtkWidget *treeview;

    unsigned int cols = pRow ? pRow->cols : 0;
    unsigned int rows = pRow ? pRow->rows : 0;

    if (!pRow || !rows || !cols)
        return gtk_label_new(_("Search failed or empty."));

    types = g_new(GType, cols);
    for (j = 0; j < cols; j++)
        types[j] = G_TYPE_STRING;
    store = gtk_list_store_newv(cols, types);
    g_free(types);

    for (i = 1; i < rows; i++) {
        gtk_list_store_append(store, &iter);
        for (j = 0; j < cols; j++)
            gtk_list_store_set(store, &iter, j, pRow->data[i][j], -1);
    }
    treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);
    renderer = gtk_cell_renderer_text_new();
    for (j = 0; j < cols; j++)
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, pRow->data[0][j], renderer, "text", j,
                                                    NULL);
    return treeview;
}
