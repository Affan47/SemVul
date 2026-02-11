hybrid_chat_window_set_icon(HybridChatWindow *window, GdkPixbuf *pixbuf)
{
    GtkTreeModel *model;
    GtkListStore *store;

    g_return_if_fail(window != NULL);

    if (!IS_USER_DEFINED_CHAT(window)) {
        return;
    }

    g_object_ref(pixbuf);
    window->icon = pixbuf;

    model = gtk_cell_view_get_model(GTK_CELL_VIEW(window->tablabel));
    store = GTK_LIST_STORE(model);

    gtk_list_store_set(store, &window->tabiter,
            TAB_STATUS_ICON_COLUMN, pixbuf,
            -1);

    model = gtk_cell_view_get_model(GTK_CELL_VIEW(window->tiplabel));
    store = GTK_LIST_STORE(model);

    gtk_list_store_set(store, &window->tipiter,
            BUDDY_ICON_COLUMN, pixbuf, -1);
}
