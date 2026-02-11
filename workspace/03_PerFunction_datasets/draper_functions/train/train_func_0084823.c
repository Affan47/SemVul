fm_unset_busy_cursor(GtkWidget* widget)
{
    if(gtk_widget_get_realized(widget))
    {
        GdkWindow* window = gtk_widget_get_window(widget);
        gdk_window_set_cursor(window, NULL);
    }
}
