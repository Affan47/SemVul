finish_get_name_owner_async (GObject *source_object,
                             GAsyncResult *res,
                             gpointer user_data)
{
    GError *error = NULL;
    gchar *owner = ibus_bus_get_name_owner_async_finish (bus,
                                                         res,
                                                         &error);
    g_assert (owner);
    g_free (owner);
    g_debug ("ibus_bus_name_get_name_owner_async_finish: OK");
    call_next_async_function ();
}
