gwy_3d_window_set_grip_cursor(Gwy3DWindow *gwy3dwindow)
{
    GtkWidget *widget = GTK_WIDGET(gwy3dwindow);
    GdkDisplay *display = gtk_widget_get_display(widget);
    GdkCursorType cursor_type;
    GdkCursor *cursor;

    if (gtk_widget_get_direction(widget) == GTK_TEXT_DIR_LTR)
        cursor_type = GDK_BOTTOM_RIGHT_CORNER;
    else
        cursor_type = GDK_BOTTOM_LEFT_CORNER;

    cursor = gdk_cursor_new_for_display(display, cursor_type);
    gdk_window_set_cursor(gwy3dwindow->resize_grip, cursor);
    gdk_cursor_unref(cursor);
}
