hslider_set_frame (GtkWidget * hslider, gint fx, gint fy)
{
    HSliderData * data = g_object_get_data ((GObject *) hslider, "hsliderdata");
    g_return_if_fail (data);

    data->fx = fx;
    data->fy = fy;
    gtk_widget_queue_draw (hslider);
}
