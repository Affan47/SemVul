gdm_display_open_session_sync (GdmDisplay    *display,
                               GPid           pid_of_caller,
                               uid_t          uid_of_caller,
                               GCancellable  *cancellable,
                               GError       **error)
{
        char *address;
        int ret;

        if (display->priv->slave_bus_proxy == NULL) {
                g_set_error (error,
                             G_DBUS_ERROR,
                             G_DBUS_ERROR_ACCESS_DENIED,
                             _("No session available yet"));
                return NULL;
        }

        address = NULL;
        ret = gdm_dbus_slave_call_open_session_sync (display->priv->slave_bus_proxy,
                                                     (int) pid_of_caller,
                                                     (int) uid_of_caller,
                                                     &address,
                                                     cancellable,
                                                     error);

        if (!ret) {
                return NULL;
        }

        return address;
}
