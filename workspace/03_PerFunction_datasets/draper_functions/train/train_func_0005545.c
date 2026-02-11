config_layouts_treeview_set_list (GtkWidget    *treeview,
                                  GtkListStore *list,
                                  gboolean      is_sortable)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    if (is_sortable) {
        gtk_tree_sortable_set_sort_func (GTK_TREE_SORTABLE (list),
                                         LAYOUT_LAYOUT_DESC_COL,
                                         sort_layout_name,
                                         NULL, NULL);
        gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (list),
                                              LAYOUT_LAYOUT_DESC_COL,
                                              GTK_SORT_ASCENDING);
    }
    gtk_tree_view_set_model (GTK_TREE_VIEW (treeview), GTK_TREE_MODEL (list));
    g_object_unref (G_OBJECT (list));

    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes (_("Layout"), renderer,
                                                       "text", LAYOUT_LAYOUT_DESC_COL,
                                                       "visible", LAYOUT_VISIBLE_COL,
                                                       NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);
    gtk_widget_show (treeview);
}
