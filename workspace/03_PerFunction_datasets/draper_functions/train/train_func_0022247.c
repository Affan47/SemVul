_bus_connect_async_cb (GObject      *source_object,
                        GAsyncResult *res,
                        gpointer      user_data)
{
    g_return_if_fail (user_data != NULL);
    g_return_if_fail (IBUS_IS_BUS (user_data));

    IBusBus *bus   = IBUS_BUS (user_data);
    GError  *error = NULL;

    bus->priv->connection =
                g_dbus_connection_new_for_address_finish (res, &error);

    if (error != NULL) {
        g_warning ("Unable to connect to ibus: %s", error->message);
        g_error_free (error);
        error = NULL;
    }

    if (bus->priv->connection != NULL) {
        ibus_bus_connect_completed (bus);
    }
    else {
        g_free (bus->priv->bus_address);
        bus->priv->bus_address = NULL;
    }


    g_object_unref (bus);
}
