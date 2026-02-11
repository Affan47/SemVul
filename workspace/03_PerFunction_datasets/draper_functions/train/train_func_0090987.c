maybe_expand_category (gpointer data)
{
    CategoryExpandPayload *payload = (CategoryExpandPayload *) data;
    GdkDeviceManager *manager;
    GdkDevice *pointer;
    GdkWindow *window;
    int x, y;
    g_assert (GTK_IS_WIDGET (payload->sidebar->tree_view));
    window = gtk_widget_get_window (GTK_WIDGET (payload->sidebar->tree_view));

    manager = gdk_display_get_device_manager (gtk_widget_get_display (GTK_WIDGET (payload->sidebar->tree_view)));
    pointer = gdk_device_manager_get_client_pointer (manager);
    gdk_window_get_device_position (window, pointer,
                                    &x, &y, NULL);
    if (pointer_is_still_in_cell (x, y, payload->rect)) {
        expand_or_collapse_category (payload->sidebar, payload->section_type, TRUE);
    }

    g_source_remove (payload->sidebar->expand_timeout_source);
    payload->sidebar->expand_timeout_source = 0;
    return FALSE;
}
