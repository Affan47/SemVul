gwy_layer_rectangle_unrealize(GwyDataViewLayer *dlayer)
{
    GwyLayerRectangle *layer;
    gint i;

    gwy_debug("");

    layer = GWY_LAYER_RECTANGLE(dlayer);
    gdk_cursor_unref(layer->resize_cursor);
    for (i = 0; i < 4; i++)
        gdk_cursor_unref(layer->corner_cursor[i]);

    GWY_DATA_VIEW_LAYER_CLASS(gwy_layer_rectangle_parent_class)->unrealize(dlayer);
}
