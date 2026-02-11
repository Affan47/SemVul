on_icon_enter_notify(GtkWidget *widget, GdkEvent *event,
                                     FmFilePropData *data)
{
    GdkWindow *window = gtk_widget_get_window(data->icon_eventbox);

    if (window && gdk_window_get_cursor(window) == NULL)
        gdk_window_set_cursor(window, gdk_cursor_new(GDK_HAND1));
    return FALSE;
}
