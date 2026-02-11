immerse_update_detail_pixbuf(ImmerseControls *controls)
{
    GwyDataField *dfield;
    GwyGradient *gradient;
    GdkPixbuf *pixbuf;
    const guchar *name;
    gchar *key;
    GQuark quark;
    gint w, h, xres, yres;

    gwy_object_unref(controls->detail);
    if (!controls->args->detail.data)
        return;

    quark = gwy_app_get_data_key_for_id(controls->args->detail.id);
    dfield = gwy_container_get_object(controls->args->detail.data, quark);
    gwy_data_view_coords_real_to_xy(GWY_DATA_VIEW(controls->view),
                                    gwy_data_field_get_xreal(dfield),
                                    gwy_data_field_get_yreal(dfield),
                                    &w, &h);
    gwy_debug("%dx%d", w, h);
    w = MAX(w, 2);
    h = MAX(h, 2);

    key = g_strdup_printf("/%d/base/palette", controls->args->image.id);
    name = NULL;
    gwy_container_gis_string_by_name(controls->args->image.data, key, &name);
    g_free(key);
    gradient = gwy_gradients_get_gradient(name);


    xres = gwy_data_field_get_xres(dfield);
    yres = gwy_data_field_get_yres(dfield);
    pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, xres, yres);
    gwy_pixbuf_draw_data_field(pixbuf, dfield, gradient);
    controls->detail = gdk_pixbuf_scale_simple(pixbuf, w, h, GDK_INTERP_TILES);
    g_object_unref(pixbuf);
}
