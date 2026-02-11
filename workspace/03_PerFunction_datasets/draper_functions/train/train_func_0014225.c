ibus_service_unregister_cb (GDBusConnection    *connection,
                            guint              *ids,
                            IBusService        *service)
{
    guint *p = ids;
    while (*p != 0) {
        g_dbus_connection_unregister_object (connection, *p++);
    }
    g_signal_handlers_disconnect_by_func (connection,
                    G_CALLBACK (ibus_service_connection_closed_cb), service);
    g_object_unref (connection);
    g_free (ids);
}
