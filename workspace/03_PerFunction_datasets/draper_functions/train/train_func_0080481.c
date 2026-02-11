resize_window(gint width, gint height, gboolean first_time)
{
    GtkRequisition req;

    if (options->resize_win == FALSE && first_time == FALSE)
        return;

    if (first_time && options->initial_geometry)
        return;

    width = MAX(width, 320);
    height = MAX(height, 240);

    if (width == rt->wid_size->width && height == rt->wid_size->height)
        return;


    gtk_widget_set_size_request(gl_widget, width, height);
    gtk_widget_size_request(GTK_WIDGET(main_window), &req);
    gtk_window_resize(main_window, req.width, req.height);


    gtk_widget_set_size_request(gl_widget, 1, 1);
}
