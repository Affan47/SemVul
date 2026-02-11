mud_connection_view_button_press_event(GtkWidget *widget, GdkEventButton *event, MudConnectionView *view)
{
    if ((event->button == 3) &&
            !(event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)))
    {
        mud_connection_view_popup(view, event);
        return TRUE;
    }

    return FALSE;
}
