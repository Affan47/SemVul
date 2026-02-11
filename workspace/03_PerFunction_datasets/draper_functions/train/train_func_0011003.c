audgui_list_update_selection (GtkWidget * list, int at, int rows)
{
    ListModel * model = (ListModel *) gtk_tree_view_get_model
     ((GtkTreeView *) list);
    g_return_if_fail (model->cbs->get_selected);
    g_return_if_fail (at >= 0 && rows >= 0 && at + rows <= model->rows);
    update_selection (list, model, at, rows);
}
