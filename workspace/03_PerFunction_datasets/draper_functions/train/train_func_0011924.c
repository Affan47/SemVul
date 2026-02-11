NotifyUser()
{
#if GTK_CHECK_VERSION(2,8,0)
    GtkWindow *window;
    window = GTK_WINDOW(g_datalist_get_data(&widset, "window-widget"));
    if (!gtk_window_has_toplevel_focus(window))
        gtk_window_set_urgency_hint(window, TRUE);
#endif
}
