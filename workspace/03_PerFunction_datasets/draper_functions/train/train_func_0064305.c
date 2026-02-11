gwy_pixmap_layer_unplugged(GwyDataViewLayer *layer)
{
    GwyPixmapLayer *pixmap_layer;

    pixmap_layer = GWY_PIXMAP_LAYER(layer);

    pixmap_layer->wants_repaint = FALSE;
    gwy_pixmap_layer_data_field_disconnect(pixmap_layer);
    gwy_signal_handler_disconnect(layer->data, pixmap_layer->item_changed_id);

    GWY_DATA_VIEW_LAYER_CLASS(gwy_pixmap_layer_parent_class)->unplugged(layer);
}
