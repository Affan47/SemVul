gwy_set_data_preview_size(GwyDataView *data_view,
                          gint max_size)
{
    GwyContainer *container;
    GwyDataField *data_field;
    GwyPixmapLayer *layer;
    gdouble zoomval, scale, xreal, yreal;
    gboolean realsquare;
    gint xres, yres;
    const gchar *prefix;
    gchar *key;

    g_return_if_fail(GWY_IS_DATA_VIEW(data_view));
    g_return_if_fail(max_size >= 2);

    container = gwy_data_view_get_data(data_view);
    g_return_if_fail(GWY_IS_CONTAINER(container));

    layer = gwy_data_view_get_base_layer(data_view);
    g_return_if_fail(GWY_IS_PIXMAP_LAYER(layer));
    prefix = gwy_pixmap_layer_get_data_key(layer);
    g_return_if_fail(prefix);

    data_field = gwy_container_get_object_by_name(container, prefix);
    g_return_if_fail(GWY_IS_DATA_FIELD(data_field));

    prefix = gwy_data_view_get_data_prefix(data_view);
    g_return_if_fail(prefix);
    key = g_strconcat(prefix, "/realsquare", NULL);
    realsquare = FALSE;
    gwy_container_gis_boolean_by_name(container, key, &realsquare);
    g_free(key);

    xres = gwy_data_field_get_xres(data_field);
    yres = gwy_data_field_get_yres(data_field);
    if (!realsquare)
        zoomval = max_size/(gdouble)MAX(xres, yres);
    else {
        xreal = gwy_data_field_get_xreal(data_field);
        yreal = gwy_data_field_get_yreal(data_field);
        scale = MAX(xres/xreal, yres/yreal);
        zoomval = max_size/(scale*MAX(xreal, yreal));
    }
    gwy_data_view_set_zoom(data_view, zoomval);
}
