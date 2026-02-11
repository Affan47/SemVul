gwy_layer_mask_set_color_key(GwyLayerMask *mask_layer,
                             const gchar *prefix)
{
    GQuark quark;

    g_return_if_fail(GWY_IS_LAYER_MASK(mask_layer));

    quark = prefix ? g_quark_try_string(prefix) : 0;
    if (quark == mask_layer->color_key)
        return;

    gwy_layer_mask_disconnect_color(mask_layer);
    mask_layer->color_key = quark;
    gwy_layer_mask_connect_color(mask_layer);

    gwy_layer_mask_changed(GWY_PIXMAP_LAYER(mask_layer));
}
