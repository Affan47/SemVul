gwy_layer_mask_unplugged(GwyDataViewLayer *layer)
{
    GwyPixmapLayer *pixmap_layer;
    GwyLayerMask *mask_layer;

    pixmap_layer = GWY_PIXMAP_LAYER(layer);
    mask_layer = GWY_LAYER_MASK(layer);

    gwy_layer_mask_disconnect_color(mask_layer);

    gwy_object_unref(pixmap_layer->pixbuf);
    GWY_DATA_VIEW_LAYER_CLASS(gwy_layer_mask_parent_class)->unplugged(layer);
}
