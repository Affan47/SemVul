hslider_new (gint min, gint max, SkinPixmapId si, gint w, gint h,
 gint fx, gint fy, gint kw, gint kh, gint knx, gint kny, gint kpx, gint kpy)
{
    GtkWidget * hslider = gtk_drawing_area_new ();
    gtk_widget_set_size_request (hslider, w, h);
    gtk_widget_add_events (hslider, GDK_BUTTON_PRESS_MASK |
     GDK_BUTTON_RELEASE_MASK | GDK_POINTER_MOTION_MASK);

    DRAW_CONNECT (hslider, hslider_draw);

    g_signal_connect (hslider, "button-press-event", (GCallback)
     hslider_button_press, NULL);
    g_signal_connect (hslider, "button-release-event", (GCallback)
     hslider_button_release, NULL);
    g_signal_connect (hslider, "motion-notify-event", (GCallback)
     hslider_motion_notify, NULL);
    g_signal_connect (hslider, "destroy", (GCallback) hslider_destroy, NULL);

    HSliderData * data = g_malloc0 (sizeof (HSliderData));
    data->min = min;
    data->max = max;
    data->pos = min;
    data->si = si;
    data->w = w;
    data->h = h;
    data->fx = fx;
    data->fy = fy;
    data->kw = kw;
    data->kh = kh;
    data->knx = knx;
    data->kny = kny;
    data->kpx = kpx;
    data->kpy = kpy;
    g_object_set_data ((GObject *) hslider, "hsliderdata", data);

    return hslider;
}
