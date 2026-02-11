constrain_size (GtkWidget *win, GtkRequisition *req, gpointer data)
{
    static gint width, height;
    GdkGeometry geo;

    if (req->width == width && req->height == height)
        return;

    width = req->width;
    height = req->height;
    geo.min_width = width;
    geo.max_width = 10000;
    geo.min_height = geo.max_height = height;
    gtk_window_set_geometry_hints (GTK_WINDOW (win), NULL, &geo,
                                   GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE);
}
