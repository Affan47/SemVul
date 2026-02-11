sp_color_wheel_size_allocate (GtkWidget *widget, GtkAllocation *allocation)
{
    SPColorWheel *wheel;

    wheel = SP_COLOR_WHEEL (widget);

    widget->allocation = *allocation;

    wheel->_center = MIN(allocation->width, allocation->height)/2;
    wheel->_inner = (3 * wheel->_center)/4;
    if ( wheel->_image )
    {
        g_free( wheel->_image );
        wheel->_image = NULL;
        wheel->_bs = 0;
    }


    sp_color_wheel_render_hue_wheel(wheel);
    sp_color_wheel_recalc_triangle(wheel);
    sp_color_wheel_render_triangle(wheel);

    if (GTK_WIDGET_REALIZED (widget)) {

        gdk_window_move_resize (widget->window, allocation->x, allocation->y, allocation->width, allocation->height);
    }
}
