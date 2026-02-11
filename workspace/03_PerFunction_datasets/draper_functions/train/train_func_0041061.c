button_on_rrelease (GtkWidget * button, ButtonCB callback)
{
    ButtonData * data = g_object_get_data ((GObject *) button, "buttondata");
    g_return_if_fail (data);

    data->on_rrelease = callback;
}
