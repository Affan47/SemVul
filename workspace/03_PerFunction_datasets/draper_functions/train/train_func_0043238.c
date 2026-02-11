on_drawing_area_motion_notify_event     (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data)
{
    gpaint_tool *tool = ACTIVE_TOOL(user_data);
    int x, y;
    GdkModifierType state;

    if (tool && tool->motion)
    {
        if (event->is_hint)
        {
            gdk_window_get_pointer (event->window, &x, &y, &state);
        }
        else
        {
            x = event->x;
            y = event->y;
            state = event->state;
        }

        if (state & GDK_BUTTON1_MASK)
        {
            (*tool->motion)(tool, x, y);
        }
    }
    return TRUE;
}
