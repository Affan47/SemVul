connect_presence_watcher (GSWatcher *watcher)
{
        DBusGConnection *bus;
        GError          *error;
        DBusGProxy      *proxy;
        guint            status;
        const char      *status_text;
        GValue           value = { 0, };

        error = NULL;
        bus = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
        if (bus == NULL) {
                g_warning ("Unable to get session bus: %s", error->message);
                g_error_free (error);
                return;
        }

        watcher->priv->presence_proxy = dbus_g_proxy_new_for_name (bus,
                                                                   GSM_SERVICE,
                                                                   GSM_PRESENCE_PATH,
                                                                   GSM_PRESENCE_INTERFACE);

        dbus_g_proxy_add_signal (watcher->priv->presence_proxy,
                                 "StatusChanged",
                                 G_TYPE_UINT,
                                 G_TYPE_INVALID);
        dbus_g_proxy_connect_signal (watcher->priv->presence_proxy,
                                     "StatusChanged",
                                     G_CALLBACK (on_presence_status_changed),
                                     watcher,
                                     NULL);
        dbus_g_proxy_add_signal (watcher->priv->presence_proxy,
                                 "StatusTextChanged",
                                 G_TYPE_STRING,
                                 G_TYPE_INVALID);
        dbus_g_proxy_connect_signal (watcher->priv->presence_proxy,
                                     "StatusTextChanged",
                                     G_CALLBACK (on_presence_status_text_changed),
                                     watcher,
                                     NULL);

        proxy = dbus_g_proxy_new_from_proxy (watcher->priv->presence_proxy,
                                             "org.freedesktop.DBus.Properties",
                                             GSM_PRESENCE_PATH);

        status = 0;
        status_text = NULL;

        error = NULL;
        dbus_g_proxy_call (proxy,
                           "Get",
                           &error,
                           G_TYPE_STRING, GSM_PRESENCE_INTERFACE,
                           G_TYPE_STRING, "status",
                           G_TYPE_INVALID,
                           G_TYPE_VALUE, &value,
                           G_TYPE_INVALID);

        if (error != NULL) {
                g_warning ("Couldn't get presence status: %s", error->message);
                g_error_free (error);
                return;
        } else {
                status = g_value_get_uint (&value);
        }

        g_value_unset (&value);

        error = NULL;
        dbus_g_proxy_call (proxy,
                           "Get",
                           &error,
                           G_TYPE_STRING, GSM_PRESENCE_INTERFACE,
                           G_TYPE_STRING, "status-text",
                           G_TYPE_INVALID,
                           G_TYPE_VALUE, &value,
                           G_TYPE_INVALID);

        if (error != NULL) {
                g_warning ("Couldn't get presence status text: %s", error->message);
                g_error_free (error);
        } else {
                status_text = g_value_get_string (&value);
        }

        set_status (watcher, status);
        set_status_text (watcher, status_text);
}
