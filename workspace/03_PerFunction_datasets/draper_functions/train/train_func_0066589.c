special_sort_tab_page_remove_track(SpecialSortTabPage *self, Track *track) {
    g_return_if_fail(SPECIAL_SORT_TAB_IS_PAGE(self));

    SpecialSortTabPagePrivate *priv = SPECIAL_SORT_TAB_PAGE_GET_PRIVATE(self);
    SortTabWidget *st_parent_widget = priv->st_widget_parent;
    SortTabWidget *st_next = sort_tab_widget_get_next(st_parent_widget);
    GList *link;


    link = g_list_find(priv->sp_members, track);
    if (link) {


        priv->sp_members = g_list_delete_link(priv->sp_members, link);
        sort_tab_widget_remove_track(st_next, track);
    }
}
