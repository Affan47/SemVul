leave_notify (GtkWidget * button, GdkEventCrossing * event)
{
    ButtonData * data = g_object_get_data ((GObject *) button, "buttondata");
    g_return_val_if_fail (data, FALSE);

    if (data->pressed || data->rpressed)
    {
        data->pressed = FALSE;
        data->rpressed = FALSE;

        if (data->type != BUTTON_TYPE_SMALL)
            gtk_widget_queue_draw (button);
    }

    return TRUE;
}
