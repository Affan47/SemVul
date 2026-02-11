bus_dbus_impl_new_connection (BusDBusImpl   *dbus,
                              BusConnection *connection)
{
    g_assert (BUS_IS_DBUS_IMPL (dbus));
    g_assert (BUS_IS_CONNECTION (connection));
    g_assert (g_list_find (dbus->connections, connection) == NULL);

    g_object_ref_sink (connection);
    dbus->connections = g_list_append (dbus->connections, connection);

    bus_connection_set_filter (connection,
                    bus_dbus_impl_connection_filter_cb, g_object_ref (dbus), g_object_unref);

    g_signal_connect (connection,
                      "destroy",
                      G_CALLBACK (bus_dbus_impl_connection_destroy_cb),
                      dbus);


    ibus_service_register ((IBusService *) dbus,
                    bus_connection_get_dbus_connection (connection), NULL);
    GList *p;
    for (p = dbus->objects; p != NULL; p = p->next) {

        ibus_service_register ((IBusService *) p->data,
                        bus_connection_get_dbus_connection (connection), NULL);
    }
    return TRUE;
}
