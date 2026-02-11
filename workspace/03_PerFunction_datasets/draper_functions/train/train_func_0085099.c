gwy_layer_lattice_button_released(GwyVectorLayer *layer,
                                  GdkEventButton *event)
{
    GwyLayerLattice *layer_lattice;
    GwyDataView *data_view;
    GdkWindow *window;
    gint x, y, i;
    gdouble xreal, yreal, xy[OBJECT_SIZE];

    if (!layer->selection)
        return FALSE;

    if (!layer->button)
        return FALSE;

    data_view = GWY_DATA_VIEW(GWY_DATA_VIEW_LAYER(layer)->parent);
    g_return_val_if_fail(data_view, FALSE);
    window = GTK_WIDGET(data_view)->window;
    layer_lattice = GWY_LAYER_LATTICE(layer);

    layer->button = 0;
    x = event->x;
    y = event->y;
    i = layer->selecting;
    gwy_debug("i = %d", i);
    gwy_data_view_coords_xy_clamp(data_view, &x, &y);
    gwy_data_view_coords_xy_to_real(data_view, x, y, &xreal, &yreal);
    gwy_layer_lattice_undraw_object(layer, window,
                                    GWY_RENDERING_TARGET_SCREEN, i);
    transform_lattice(layer_lattice, xreal, yreal, xy);
    gwy_selection_set_object(layer->selection, i, xy);
    gwy_layer_lattice_draw_object(layer, window, GWY_RENDERING_TARGET_SCREEN, i);

    layer->selecting = -1;

    gwy_selection_finished(layer->selection);

    return FALSE;
}
