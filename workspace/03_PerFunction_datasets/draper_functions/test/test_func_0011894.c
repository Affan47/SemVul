_st_get_compilation_entry(NormalSortTabPage *self) {
    TabEntry *entry;
    guint i;

    NormalSortTabPagePrivate *priv = NORMAL_SORT_TAB_PAGE_GET_PRIVATE(self);
    i = 1;
    while ((entry = (TabEntry *) g_list_nth_data(priv->entries, i)) != NULL) {
        if (entry->compilation)
            break;
        ++i;
    }
    return entry;
}
