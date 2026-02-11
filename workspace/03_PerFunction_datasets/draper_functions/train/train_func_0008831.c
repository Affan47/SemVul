vnc_display_set_scaling(VncDisplay *obj,
                                 gboolean enable)
{
    int ww, wh;

    obj->priv->allow_scaling = enable;

    if (obj->priv->fb != NULL) {
        gdk_drawable_get_size(gtk_widget_get_window(GTK_WIDGET(obj)), &ww, &wh);
        gtk_widget_queue_draw_area(GTK_WIDGET(obj), 0, 0, ww, wh);
    }

    return TRUE;
}
