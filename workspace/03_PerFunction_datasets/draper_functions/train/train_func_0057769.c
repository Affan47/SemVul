audgui_list_insert_rows (GtkWidget * list, int at, int rows)
{
    ListModel * model = (ListModel *) gtk_tree_view_get_model
     ((GtkTreeView *) list);
    g_return_if_fail (at >= 0 && at <= model->rows && rows >= 0);

    model->rows += rows;
    if (model->highlight >= at)
        model->highlight += rows;

    GtkTreeIter iter = {.user_data = GINT_TO_POINTER (at)};
    GtkTreePath * path = gtk_tree_path_new_from_indices (at, -1);

    for (int i = rows; i --; )
        gtk_tree_model_row_inserted ((GtkTreeModel *) model, path, & iter);

    gtk_tree_path_free (path);

    if (model->cbs->get_selected)
        update_selection (list, model, at, rows);
}
