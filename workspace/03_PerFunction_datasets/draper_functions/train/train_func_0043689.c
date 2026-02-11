gwy_curve_set_channels(GwyCurve *c,
                       gint num_channels,
                       GwyRGBA *colors)
{
    gint width, height;
    gint i;
    GwyRGBA color = { 1.0, 0.0, 0.0, 1.0 };

    if (c->num_channels != num_channels) {


        for (i = 0; i < c->num_channels; i++) {
            if (c->channel_data[i].points)
                g_free(c->channel_data[i].points);
            if (c->channel_data[i].ctlpoints)
                g_free(c->channel_data[i].ctlpoints);
        }
        g_free(c->channel_data);


        c->num_channels = num_channels;

        c->channel_data = g_new(GwyChannelData, c->num_channels);
        for (i = 0; i < c->num_channels; i++) {
            c->channel_data[i].num_points = 0;
            c->channel_data[i].points = NULL;
            c->channel_data[i].num_ctlpoints = 2;
            c->channel_data[i].ctlpoints = g_new(GwyPoint, 2);
            c->channel_data[i].ctlpoints[0].x = c->min_x;
            c->channel_data[i].ctlpoints[0].y = c->min_y;
            c->channel_data[i].ctlpoints[1].x = c->max_x;
            c->channel_data[i].ctlpoints[1].y = c->max_y;
            c->channel_data[i].color = color;
        }
    }

    if (colors)
        for (i = 0; i < c->num_channels; i++)
            c->channel_data[i].color = colors[i];

    if (c->pixmap) {
        width = GTK_WIDGET(c)->allocation.width - RADIUS * 2;
        height = GTK_WIDGET(c)->allocation.height - RADIUS * 2;

        gwy_curve_interpolate(c, width, height);
        gwy_curve_draw(c, width, height);
    }
}
