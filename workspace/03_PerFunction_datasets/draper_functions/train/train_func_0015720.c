gwy_pixmap_layer_set_data_key(GwyPixmapLayer *pixmap_layer,
                              const gchar *key)
{
    GwyDataViewLayer *layer;
    GQuark quark;

    g_return_if_fail(GWY_IS_PIXMAP_LAYER(pixmap_layer));

    quark = key ? g_quark_from_string(key) : 0;
    if (pixmap_layer->data_key == quark)
        return;

    layer = GWY_DATA_VIEW_LAYER(pixmap_layer);
    if (!layer->data) {
        pixmap_layer->data_key = quark;
        g_object_notify(G_OBJECT(pixmap_layer), "data-key");
        return;
    }

    gwy_signal_handler_disconnect(layer->data, pixmap_layer->item_changed_id);
    gwy_pixmap_layer_data_field_disconnect(pixmap_layer);
    pixmap_layer->data_key = quark;
    gwy_pixmap_layer_data_field_connect(pixmap_layer);
    gwy_pixmap_layer_container_connect(pixmap_layer, g_quark_to_string(quark));

    pixmap_layer->wants_repaint = TRUE;
    g_object_notify(G_OBJECT(pixmap_layer), "data-key");
    gwy_data_view_layer_updated(GWY_DATA_VIEW_LAYER(pixmap_layer));
}
