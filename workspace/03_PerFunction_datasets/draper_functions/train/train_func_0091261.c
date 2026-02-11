gxi_selected_enc_activated_cb (GtkTreeView *view, GtkTreePath *path,
                               GtkTreeViewColumn *column, GncXmlImportData *data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    model = gtk_tree_view_get_model (data->selected_encs_view);
    if (!gtk_tree_model_get_iter (model, &iter, path))
        return;
    gxi_remove_encoding (data, model, &iter);
}
