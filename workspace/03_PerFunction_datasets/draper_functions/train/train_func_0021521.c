gwy_layer_basic_get_range_type(GwyLayerBasic *basic_layer)
{
    GwyLayerBasicRangeType range_type;
    GwyContainer *data;

    g_return_val_if_fail(GWY_IS_LAYER_BASIC(basic_layer), 0);

    data = GWY_DATA_VIEW_LAYER(basic_layer)->data;
    range_type = GPOINTER_TO_UINT(basic_layer->default_range_type);
    if (data && basic_layer->range_type_key)
        gwy_container_gis_enum(data, basic_layer->range_type_key, &range_type);

    return range_type;
}
