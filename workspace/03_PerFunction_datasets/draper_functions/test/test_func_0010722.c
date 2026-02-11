_icon_click_event(GtkWidget *widget, GdkEventButton *event,
                                  FmFilePropData *data)
{

    if (event->button == 1 && gtk_widget_get_can_focus(data->icon_eventbox))
    {

        _change_icon(gtk_widget_get_toplevel(widget), data);
        return TRUE;
    }
    return FALSE;
}
