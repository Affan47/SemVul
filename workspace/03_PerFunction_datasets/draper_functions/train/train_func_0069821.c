hslider_set_pos (GtkWidget * hslider, gint pos)
{
    HSliderData * data = g_object_get_data ((GObject *) hslider, "hsliderdata");
    g_return_if_fail (data);

    if (data->pressed)
        return;

    data->pos = CLAMP (pos, data->min, data->max);
    gtk_widget_queue_draw (hslider);
}
