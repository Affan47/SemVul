gwy_app_3d_window_set_data2(Gwy3DWindow *gwy3dwindow,
                            gint id,
                            gboolean mask)
{
    Gwy3DView *view;
    GQuark key;
    GwyPixmapLayer *ovplay[2];
    GwyDataViewLayer* dvl;
    guchar name[48];


    view = GWY_3D_VIEW(gwy_3d_window_get_3d_view(gwy3dwindow));

    key = gwy_app_get_data_key_for_id(id);

    ovplay[0] = gwy_layer_basic_new();


    dvl = GWY_DATA_VIEW_LAYER(ovplay[0]);
    dvl->data = view->data;
    g_object_ref(dvl->data);

    gwy_pixmap_layer_set_data_key(ovplay[0], g_quark_to_string(key));
    gwy_layer_basic_set_gradient_key(GWY_LAYER_BASIC(ovplay[0]),
                                     gwy_3d_view_get_gradient_key(view));
    g_snprintf(name, sizeof(name), "/%d/base",  id);
    gwy_layer_basic_set_min_max_key(GWY_LAYER_BASIC(ovplay[0]),
                                    name);
    g_snprintf(name, sizeof(name), "/%d/base/range-type", id);
    gwy_layer_basic_set_range_type_key(GWY_LAYER_BASIC(ovplay[0]),
                                    name);

    if (mask) {
        key = gwy_app_get_mask_key_for_id(id);
        ovplay[1] = gwy_layer_mask_new();
        dvl = GWY_DATA_VIEW_LAYER(ovplay[1]);
        dvl->data = view->data;
        g_object_ref(dvl->data);
        gwy_pixmap_layer_set_data_key(ovplay[1], g_quark_to_string(key));
        gwy_layer_mask_set_color_key(GWY_LAYER_MASK(ovplay[1]),
                                     g_quark_to_string(key));
        gwy_3d_view_set_ovlay(view, ovplay, 2);
    }
    else {
        gwy_3d_view_set_ovlay(view, ovplay, 1);
    };
}
