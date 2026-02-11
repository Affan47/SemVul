gwy_data_view_set_layer(GwyDataView *data_view,
                        gpointer which,
                        gulong *hid,
                        GwyDataViewLayer *layer,
                        GwyDataViewLayerType type)
{
    GwyDataViewLayer **which_layer;

    which_layer = (GwyDataViewLayer**)which;
    if (layer == *which_layer)
        return;
    if (*which_layer) {
        if (hid) {
            g_signal_handler_disconnect(*which_layer, *hid);
            *hid = 0;
        }
        if (GTK_WIDGET_REALIZED(GTK_WIDGET(data_view)))
            gwy_data_view_layer_unrealize(GWY_DATA_VIEW_LAYER(*which_layer));


        gwy_data_view_layer_unplugged(*which_layer);
        (*which_layer)->parent = NULL;
        g_object_unref(*which_layer);
        g_signal_emit(data_view, data_view_signals[LAYER_UNPLUGGED], 0, type);
    }
    if (layer) {
        g_assert(layer->parent == NULL);
        g_object_ref(layer);
        gtk_object_sink(GTK_OBJECT(layer));
        layer->parent = (GtkWidget*)data_view;
        if (hid)
            *hid = g_signal_connect_swapped(layer, "updated",
                                            G_CALLBACK(gwy_data_view_update),
                                            data_view);
        gwy_data_view_layer_plugged(layer);
        if (GTK_WIDGET_REALIZED(GTK_WIDGET(data_view)))
            gwy_data_view_layer_realize(GWY_DATA_VIEW_LAYER(layer));
    }
    data_view->layers_changed = TRUE;
    *which_layer = layer;
    g_signal_emit(data_view, data_view_signals[LAYER_PLUGGED], 0, type);
    gwy_data_view_update(data_view);
}
