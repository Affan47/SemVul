on_tree_view_select_all_char (GtkTreeSelection     *selection,
                              gpointer              data)
{
    CharTreeViewData *tv_data = (CharTreeViewData*) data;
    GtkWidget *viewport;
    GtkWidget *window;
    GtkTreeModel *model;
    GtkTreeIter iter;
    unsigned int start, end;

    g_return_if_fail (data != NULL);

    viewport = GTK_WIDGET (tv_data->viewport);
    window = GTK_WIDGET (tv_data->window);
    if (!gtk_tree_selection_get_selected (selection, &model, &iter)) {
        return;
    }
    gtk_tree_model_get (model, &iter,
                        CHAR_BLOCK_START_COL, &start,
                        CHAR_BLOCK_END_COL, &end, -1);
    destroy_all_char_view_table (viewport, INPUT_PAD_GTK_WINDOW (window));
    append_all_char_view_table (viewport, start, end, window);
}
