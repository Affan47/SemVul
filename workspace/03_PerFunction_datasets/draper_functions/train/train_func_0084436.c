gwy_color_axis_expose(GtkWidget *widget,
                      GdkEventExpose *event)
{
    GwyColorAxis *axis;
    GdkGC *gc;

    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(GWY_IS_COLOR_AXIS(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

    if (event->count > 0)
        return FALSE;

    axis = GWY_COLOR_AXIS(widget);
    gc = widget->style->fg_gc[GTK_WIDGET_STATE(widget)];

    if (axis->orientation == GTK_ORIENTATION_HORIZONTAL)
        gdk_draw_pixbuf(widget->window, gc, axis->stripe,
                        0, 0,
                        0, 0,
                        gdk_pixbuf_get_width(axis->stripe),
                        gdk_pixbuf_get_height(axis->stripe),
                        GDK_RGB_DITHER_NONE, 0, 0);
    else
        gdk_draw_pixbuf(widget->window, gc, axis->stripe,
                        0, 0,
                        0, 0,
                        gdk_pixbuf_get_width(axis->stripe),
                        gdk_pixbuf_get_height(axis->stripe),
                        GDK_RGB_DITHER_NONE, 0, 0);
    gwy_color_axis_draw_labels_ticks(axis);
    return FALSE;
}
