_create_input_context_async_step_one_done (GDBusConnection    *connection,
                                           GAsyncResult       *res,
                                           GSimpleAsyncResult *simple)
{
    GError *error = NULL;
    GVariant *variant = g_dbus_connection_call_finish (connection, res, &error);

    if (variant == NULL) {
        g_simple_async_result_set_from_error (simple, error);
        g_error_free (error);
        g_simple_async_result_complete_in_idle (simple);
        g_object_unref (simple);
        return;
    }

    if (g_dbus_connection_is_closed (connection)) {


        g_simple_async_result_set_error (simple,
                G_DBUS_ERROR, G_DBUS_ERROR_FAILED, "Connection is closed.");
        g_simple_async_result_complete_in_idle (simple);
        return;
    }

    const gchar *path = NULL;
    g_variant_get (variant, "(&o)", &path);


    IBusBus *bus = (IBusBus *)g_async_result_get_source_object (
            (GAsyncResult *)simple);
    g_assert (IBUS_IS_BUS (bus));

    GCancellable *cancellable =
            (GCancellable *)g_object_get_data ((GObject *)simple,
                                               "cancellable");

    ibus_input_context_new_async (path,
            bus->priv->connection,
            cancellable,
            (GAsyncReadyCallback)_create_input_context_async_step_two_done,
            simple);

    g_object_unref (bus);
}
