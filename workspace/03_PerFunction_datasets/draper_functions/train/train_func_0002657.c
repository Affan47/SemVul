ibus_config_new (GDBusConnection  *connection,
                 GCancellable     *cancellable,
                 GError          **error)
{
    g_assert (G_IS_DBUS_CONNECTION (connection));

    GInitable *initable;

    GDBusProxyFlags flags = G_DBUS_PROXY_FLAGS_DO_NOT_AUTO_START |
                            G_DBUS_PROXY_FLAGS_DO_NOT_LOAD_PROPERTIES |
                            G_DBUS_PROXY_FLAGS_DO_NOT_CONNECT_SIGNALS;

    initable = g_initable_new (IBUS_TYPE_CONFIG,
                               cancellable,
                               error,
                               "g-connection",      connection,
                               "g-flags",           flags,
                               "g-name",            IBUS_SERVICE_CONFIG,
                               "g-interface-name",  IBUS_INTERFACE_CONFIG,
                               "g-object-path",     IBUS_PATH_CONFIG,
                               "g-default-timeout", ibus_get_timeout (),
                               NULL);
    if (initable == NULL)
        return NULL;

    if (g_dbus_proxy_get_name_owner (G_DBUS_PROXY (initable)) == NULL) {

        g_set_error (error,
                     IBUS_ERROR,
                     IBUS_ERROR_NO_CONFIG,
                     "Configuration daemon is not running.");
        g_object_unref (initable);
        return NULL;
    }


    IBUS_PROXY (initable)->own = FALSE;

    return IBUS_CONFIG (initable);
}
