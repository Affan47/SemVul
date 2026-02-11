gwy_curve_button_release(GtkWidget *widget,
                         G_GNUC_UNUSED GdkEventButton *event,
                         GwyCurve *c)
{
    gint src, dst;
    gint width, height;
    GtkWidget *w;
    GwyChannelData *channel;

    w = GTK_WIDGET(c);
    width = w->allocation.width - RADIUS * 2;
    height = w->allocation.height - RADIUS * 2;

    gtk_grab_remove(widget);

    channel = &c->channel_data[c->grab_channel];


    if (c->curve_type != GWY_CURVE_TYPE_FREE) {
        for (src = dst = 0; src < channel->num_ctlpoints; ++src) {
            if (channel->ctlpoints[src].x >= c->min_x) {
                memcpy(channel->ctlpoints + dst, channel->ctlpoints + src,
                       sizeof(GwyPoint));
                ++dst;
            }
        }
        if (dst < src) {
            channel->num_ctlpoints -= (src - dst);
            if (channel->num_ctlpoints <= 0) {
                channel->num_ctlpoints = 1;
                channel->ctlpoints[0].x = c->min_x;
                channel->ctlpoints[0].y = c->min_y;
                gwy_curve_interpolate(c, width, height);
                gwy_curve_draw(c, width, height);
            }
            channel->ctlpoints =
                g_realloc(channel->ctlpoints,
                          channel->num_ctlpoints * sizeof(GwyPoint));
        }
    }
    c->grab_point = -1;
    c->grab_channel = -1;

    g_signal_emit(c, curve_edited_signal, 0);
    return TRUE;
}
