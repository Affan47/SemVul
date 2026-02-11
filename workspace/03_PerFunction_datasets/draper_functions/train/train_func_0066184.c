on_bus_gotten (GObject               *source_object,
               GAsyncResult          *res,
               GsdOrientationManager *manager)
{
        GDBusConnection *connection;
        GError *error = NULL;

        connection = g_bus_get_finish (res, &error);
        if (connection == NULL) {
                g_warning ("Could not get session bus: %s", error->message);
                g_error_free (error);
                return;
        }
        manager->priv->connection = connection;

        g_dbus_connection_register_object (connection,
                                           GSD_ORIENTATION_DBUS_PATH,
                                           manager->priv->introspection_data->interfaces[0],
                                           NULL,
                                           NULL,
                                           NULL,
                                           NULL);

        g_dbus_proxy_new (manager->priv->connection,
                          G_DBUS_PROXY_FLAGS_NONE,
                          NULL,
                          GSD_DBUS_NAME ".XRANDR",
                          GSD_DBUS_PATH "/XRANDR",
                          GSD_DBUS_BASE_INTERFACE ".XRANDR_2",
                          NULL,
                          (GAsyncReadyCallback) xrandr_ready_cb,
                          manager);

        manager->priv->name_id = g_bus_own_name_on_connection (connection,
                                                               GSD_ORIENTATION_DBUS_NAME,
                                                               G_BUS_NAME_OWNER_FLAGS_NONE,
                                                               NULL,
                                                               NULL,
                                                               NULL,
                                                               NULL);
}
