sort_tab_widget_sort(SortTabWidget *self, enum GtkPodSortTypes order) {
    if (! SORT_TAB_IS_WIDGET(self)) {
        return;
    }

    SortTabWidgetPrivate *priv = SORT_TAB_WIDGET_GET_PRIVATE(self);
    _sort_tab_widget_sort_internal(self, order);

    sort_tab_widget_sort(priv->next, order);
}
