normal_sort_tab_page_stop_editing(NormalSortTabPage *self, gboolean cancel) {
    g_return_if_fail(NORMAL_SORT_TAB_IS_PAGE(self));
    GList *cells;
    GtkTreeViewColumn *col;
    gtk_tree_view_get_cursor(GTK_TREE_VIEW(self), NULL, &col);

    if (col) {
        cells = gtk_cell_layout_get_cells(GTK_CELL_LAYOUT (col));
        g_list_foreach(cells, (GFunc) _cell_renderer_stop_editing, GINT_TO_POINTER((gint) cancel));
        g_list_free(cells);
    }
}
