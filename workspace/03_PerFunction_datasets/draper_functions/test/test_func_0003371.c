sp_color_wheel_button_press (GtkWidget *widget, GdkEventButton *event)
{
    SPColorWheel *wheel;

    wheel = SP_COLOR_WHEEL (widget);

    if (event->button == 1) {
        gint cx, cw;
        cx = widget->style->xthickness;
        cw = widget->allocation.width - 2 * cx;
        gboolean grabbed = FALSE;

        {
            double dx = event->x - wheel->_center;
            double dy = event->y - wheel->_center;
            gint hyp = static_cast<gint>(ABS(dx*dx) + ABS(dy*dy));
            if ( hyp <= (wheel->_center*wheel->_center) )
            {
                if ( hyp >= (wheel->_inner*wheel->_inner) )
                {
                    gdouble rot = atan2( dy, -dx );
                    sp_color_wheel_set_hue (wheel, (rot + M_PI) / (2.0 * M_PI));

                    wheel->_inTriangle = FALSE;
                    grabbed = TRUE;
                }
                else if ( wheel->_triangle && gdk_region_point_in( wheel->_triangle, (gint)event->x, (gint)event->y ) )
                {
                    wheel->_inTriangle = TRUE;
                    sp_color_wheel_process_in_triangle( wheel, event->x, event->y );
                    grabbed = TRUE;
                }
            }
        }

        if ( grabbed )
        {
            gtk_widget_queue_draw( widget );
            gtk_widget_grab_focus( widget );

            wheel->dragging = TRUE;
#ifdef DUMP_CHANGE_INFO
            {
                SPColor color;
                sp_color_wheel_get_color( wheel, &color );
                g_message( "%s:%d: About to signal %s to color %08x in %s", __FILE__, __LINE__,
                           "CHANGED",
                           color.toRGBA32( 0 ), FOO_NAME(wheel));
            }
#endif
            gtk_signal_emit (GTK_OBJECT (wheel), wheel_signals[CHANGED]);
            gdk_pointer_grab (widget->window, FALSE,
                              (GdkEventMask)(GDK_POINTER_MOTION_MASK | GDK_BUTTON_RELEASE_MASK),
                              NULL, NULL, event->time);
        }
    }

    return TRUE;
}
