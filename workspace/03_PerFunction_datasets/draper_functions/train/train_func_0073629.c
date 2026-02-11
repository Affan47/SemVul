sort_tab_widget_set_sort_enablement(SortTabWidget *self, gboolean enable) {
    if (! SORT_TAB_IS_WIDGET(self)) {
        gtkpod_set_sort_enablement(enable);
        return;
    }

    SortTabWidgetPrivate *priv = SORT_TAB_WIDGET_GET_PRIVATE(self);
    GtkTreeModel *model = priv->model;
    SortTabWidget *next = sort_tab_widget_get_next(self);

    if (enable) {
        priv->disable_sort_count--;
        if (priv->disable_sort_count < 0)
            fprintf(stderr, "Programming error: disable_count < 0\n");
        if (priv->disable_sort_count == 0) {

            if (prefs_get_int("st_sort") != SORT_NONE) {
                if (sort_tab_widget_get_category(self) != ST_CAT_SPECIAL && model) {
                    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE (model), ST_COLUMN_ENTRY, prefs_get_int("st_sort"));
                }
            }
            sort_tab_widget_set_sort_enablement(next, enable);
        }
    }
    else {
        if (priv->disable_sort_count == 0) {

            if (prefs_get_int("st_sort") != SORT_NONE) {
                if (sort_tab_widget_get_category(self) != ST_CAT_SPECIAL && model) {
                    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE (model), GTK_TREE_SORTABLE_UNSORTED_SORT_COLUMN_ID, prefs_get_int("st_sort"));
                }
            }
            sort_tab_widget_set_sort_enablement(next, enable);
        }
        priv->disable_sort_count++;
    }
}
