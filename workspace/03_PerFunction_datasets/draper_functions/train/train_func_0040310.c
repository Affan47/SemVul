gwy_vector_layer_set_selection_key(GwyVectorLayer *layer,
                                   const gchar *key)
{
    GwyDataViewLayer *view_layer;
    GQuark quark;

    g_return_if_fail(GWY_IS_VECTOR_LAYER(layer));
    quark = key ? g_quark_from_string(key) : 0;
    if (layer->selection_key == quark)
        return;
    view_layer = GWY_DATA_VIEW_LAYER(layer);
    if (!view_layer->data) {
        layer->selection_key = quark;
        g_object_notify(G_OBJECT(layer), "selection-key");
        return;
    }
    gwy_signal_handler_disconnect(view_layer->data, layer->item_changed_id);
    gwy_vector_layer_selection_disconnect(layer);
    layer->selection_key = quark;
    gwy_vector_layer_selection_connect(layer);
    gwy_vector_layer_container_connect(layer, g_quark_to_string(quark));


    g_object_notify(G_OBJECT(layer), "selection-key");
    gwy_data_view_layer_updated(GWY_DATA_VIEW_LAYER(layer));
}
