gwy_data_window_data_view_updated(GwyDataWindow *data_window)
{
    GwyContainer *data;
    GwyDataView *view;
    GwyPixmapLayer *layer;
    gdouble min, max;
    const gchar *key;
    const guchar *gradname;

    data = gwy_data_window_get_data(data_window);
    g_return_if_fail(GWY_IS_CONTAINER(data));

    view = GWY_DATA_VIEW(data_window->data_view);
    layer = gwy_data_view_get_base_layer(view);
    key = gwy_pixmap_layer_get_data_key(layer);
    gwy_layer_basic_get_range(GWY_LAYER_BASIC(layer), &min, &max);
    gwy_color_axis_set_range(GWY_COLOR_AXIS(data_window->coloraxis), min, max);
    key = gwy_layer_basic_get_gradient_key(GWY_LAYER_BASIC(layer));
    if (key && gwy_container_gis_string_by_name(data, key, &gradname))
        gwy_color_axis_set_gradient(GWY_COLOR_AXIS(data_window->coloraxis),
                                    gradname);
    gwy_data_window_size_allocate(GTK_WIDGET(data_window), NULL);
    gwy_data_window_update_units(data_window);
}
