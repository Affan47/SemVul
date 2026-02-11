bus_factory_proxy_new (BusConnection *connection)
{
    g_assert (BUS_IS_CONNECTION (connection));
    BusFactoryProxy *factory;

    GDBusProxyFlags flags = G_DBUS_PROXY_FLAGS_DO_NOT_AUTO_START |
                            G_DBUS_PROXY_FLAGS_DO_NOT_LOAD_PROPERTIES;
    factory = (BusFactoryProxy *) g_initable_new (
            BUS_TYPE_FACTORY_PROXY,
            NULL, NULL,
            "g-object-path",     IBUS_PATH_FACTORY,
            "g-interface-name",  IBUS_INTERFACE_FACTORY,
            "g-connection",      bus_connection_get_dbus_connection (connection),
            "g-default-timeout", g_gdbus_timeout,
            "g-flags",           flags,
            NULL);

    return factory;
}
