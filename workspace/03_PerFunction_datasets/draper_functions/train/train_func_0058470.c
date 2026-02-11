gwy_layer_basic_gradient_connect(GwyLayerBasic *basic_layer)
{
    GwyDataViewLayer *layer;
    const guchar *s = NULL;

    g_return_if_fail(!basic_layer->gradient);
    layer = GWY_DATA_VIEW_LAYER(basic_layer);
    if (basic_layer->gradient_key)
        gwy_container_gis_string(layer->data, basic_layer->gradient_key, &s);
    basic_layer->gradient = gwy_gradients_get_gradient(s);
    gwy_resource_use(GWY_RESOURCE(basic_layer->gradient));
    basic_layer->gradient_id
        = g_signal_connect_swapped(basic_layer->gradient, "data-changed",
                                   G_CALLBACK(gwy_layer_basic_changed), layer);
}
