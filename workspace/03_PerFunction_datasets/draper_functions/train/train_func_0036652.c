gwy_layer_mask_get_color(GwyLayerMask *mask_layer)
{
    GwyContainer *data;
    GwyRGBA color = { 0, 0, 0, 0 };

    g_return_val_if_fail(GWY_IS_LAYER_MASK(mask_layer), color);
    data = GWY_DATA_VIEW_LAYER(mask_layer)->data;
    g_return_val_if_fail(data, color);

    if (!mask_layer->color_key)
        return color;

    gwy_rgba_get_from_container(&color, GWY_DATA_VIEW_LAYER(mask_layer)->data,
                                g_quark_to_string(mask_layer->color_key));

    return color;
}
