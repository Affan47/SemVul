gwy_data_view_layer_realize(GwyDataViewLayer *layer)
{
    void (*method)(GwyDataViewLayer*);

    gwy_debug("");
    g_return_if_fail(GWY_IS_DATA_VIEW_LAYER(layer));
    method = GWY_DATA_VIEW_LAYER_GET_CLASS(layer)->realize;
    if (method)
        method(layer);
}
