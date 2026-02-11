register_accounts_daemon (Daemon *daemon)
{
        GError *error = NULL;

        daemon->priv->authority = polkit_authority_get_sync (NULL, &error);

        if (daemon->priv->authority == NULL) {
                if (error != NULL) {
                        g_critical ("error getting polkit authority: %s", error->message);
                        g_error_free (error);
                }
                goto error;
        }

        daemon->priv->bus_connection = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, &error);
        if (daemon->priv->bus_connection == NULL) {
                if (error != NULL) {
                        g_critical ("error getting system bus: %s", error->message);
                        g_error_free (error);
                }
                goto error;
        }

        if (!g_dbus_interface_skeleton_export (G_DBUS_INTERFACE_SKELETON (daemon),
                                               daemon->priv->bus_connection,
                                               "/org/freedesktop/Accounts",
                                               &error)) {
                if (error != NULL) {
                        g_critical ("error exporting interface: %s", error->message);
                        g_error_free (error);
                }
                goto error;
        }

        return TRUE;

 error:
        return FALSE;
}
