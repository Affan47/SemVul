_remove_scroll_row_timeout(GtkWidget *widget) {
    g_return_if_fail(widget);

    g_object_set_data(G_OBJECT(widget), "scroll_row_timeout", NULL);
    g_object_set_data(G_OBJECT(widget), "scroll_row_times", NULL);
}
