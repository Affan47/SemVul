gwy_vector_layer_selection_disconnect(GwyVectorLayer *layer)
{
    if (!layer->selection)
        return;

    gwy_signal_handler_disconnect(layer->selection,
                                  layer->selection_changed_id);
    layer->selecting = -1;
    gwy_object_unref(layer->selection);
}
