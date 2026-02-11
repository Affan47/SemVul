gwy_app_data_browser_create_3d(G_GNUC_UNUSED GwyAppDataBrowser *browser,
                               GwyAppDataProxy *proxy,
                               gint id)
{
    GtkWidget *view3d, *window3d;
    GObject *dfield = NULL;
    GwyApp3DAssociation *assoc;
    gchar key[40];
    const guchar *palette = NULL;
    guint len;

    g_snprintf(key, sizeof(key), "/%d/data", id);
    gwy_container_gis_object_by_name(proxy->container, key, &dfield);
    g_return_val_if_fail(GWY_IS_DATA_FIELD(dfield), NULL);

    g_snprintf(key, sizeof(key), "/%d/base/palette", id);
    gwy_container_gis_string_by_name(proxy->container, key, &palette);

    view3d = gwy_3d_view_new(proxy->container);

    g_snprintf(key, sizeof(key), "/%d/", id);
    len = strlen(key);

    g_strlcat(key, "3d", sizeof(key));


    _gwy_app_3d_view_init_setup(proxy->container, key);
    gwy_3d_view_set_setup_prefix(GWY_3D_VIEW(view3d), key);

    key[len] = '\0';
    g_strlcat(key, "data", sizeof(key));
    gwy_3d_view_set_data_key(GWY_3D_VIEW(view3d), key);


    key[len] = '\0';
    g_strlcat(key, "3d/palette", sizeof(key));
    gwy_3d_view_set_gradient_key(GWY_3D_VIEW(view3d), key);

    if (palette)
        gwy_container_set_string_by_name(proxy->container, key,
                                         g_strdup(palette));

    key[len] = '\0';
    g_strlcat(key, "3d/material", sizeof(key));
    gwy_3d_view_set_material_key(GWY_3D_VIEW(view3d), key);

    window3d = gwy_3d_window_new(GWY_3D_VIEW(view3d));

    gwy_app_update_3d_window_title(GWY_3D_WINDOW(window3d), id);

    g_signal_connect(window3d, "destroy",
                     G_CALLBACK(gwy_app_data_proxy_3d_destroyed), proxy);

    assoc = g_new(GwyApp3DAssociation, 1);
    assoc->window = GWY_3D_WINDOW(window3d);
    assoc->id = id;
    proxy->associated_3d = g_list_prepend(proxy->associated_3d, assoc);

    _gwy_app_3d_window_setup(GWY_3D_WINDOW(window3d));
    gtk_widget_show_all(window3d);

    return window3d;
}
