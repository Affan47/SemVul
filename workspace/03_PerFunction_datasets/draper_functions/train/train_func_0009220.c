gwy_axis_size_allocate(GtkWidget *widget,
                       GtkAllocation *allocation)
{
    GwyAxis *axis;

    gwy_debug("");

    g_return_if_fail(widget != NULL);
    g_return_if_fail(GWY_IS_AXIS(widget));
    g_return_if_fail(allocation != NULL);

    widget->allocation = *allocation;

    axis = GWY_AXIS(widget);

    if (GTK_WIDGET_REALIZED(widget))
        gdk_window_move_resize(widget->window,
                               allocation->x, allocation->y,
                               allocation->width, allocation->height);
    gwy_axis_adjust(axis, allocation->width, allocation->height);
}
