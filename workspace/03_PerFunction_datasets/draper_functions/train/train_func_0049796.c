gwy_layer_axis_motion_notify(GwyVectorLayer *layer,
                             GdkEventMotion *event)
{
    GwyDataView *data_view;
    GwyOrientation orientation;
    GdkWindow *window;
    GdkCursor *cursor;
    gint x, y, i;
    gdouble xreal, yreal, rcoord, xy[OBJECT_SIZE];

    if (!layer->selection)
        return FALSE;


    if (!layer->editable)
        return FALSE;

    data_view = GWY_DATA_VIEW(GWY_DATA_VIEW_LAYER(layer)->parent);
    g_return_val_if_fail(data_view, FALSE);
    window = GTK_WIDGET(data_view)->window;

    i = layer->selecting;
    if (i > -1)
        gwy_selection_get_object(layer->selection, i, xy);

    if (event->is_hint)
        gdk_window_get_pointer(window, &x, &y, NULL);
    else {
        x = event->x;
        y = event->y;
    }
    gwy_debug("x = %d, y = %d", x, y);
    gwy_data_view_coords_xy_clamp(data_view, &x, &y);
    gwy_data_view_coords_xy_to_real(data_view, x, y, &xreal, &yreal);
    orientation = GWY_SELECTION_AXIS(layer->selection)->orientation;
    rcoord = (orientation == GWY_ORIENTATION_VERTICAL) ? xreal : yreal;
    if (i > -1 && rcoord == xy[0])
        return FALSE;

    if (!layer->button) {
        i = gwy_layer_axis_near_point(layer, xreal, yreal);
        cursor = GWY_LAYER_AXIS(layer)->near_cursor;
        gdk_window_set_cursor(window, i == -1 ? NULL : cursor);
        return FALSE;
    }

    g_assert(layer->selecting != -1);
    gwy_layer_axis_undraw_object(layer, window,
                                 GWY_RENDERING_TARGET_SCREEN, i);
    xy[0] = rcoord;
    gwy_selection_set_object(layer->selection, i, xy);
    gwy_layer_axis_draw_object(layer, window,
                               GWY_RENDERING_TARGET_SCREEN, i);

    return FALSE;
}
