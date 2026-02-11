gsm_shell_disconnect_from_bus (GsmShell *shell)
{
        g_clear_object (&shell->priv->bus_proxy);
        g_clear_object (&shell->priv->proxy);

        if (shell->priv->bus_connection != NULL) {
                DBusConnection *connection;
                connection = dbus_g_connection_get_connection (shell->priv->bus_connection);
                dbus_connection_remove_filter (connection,
                                               gsm_shell_bus_filter,
                                               shell);

                dbus_g_connection_unref (shell->priv->bus_connection);
                shell->priv->bus_connection = NULL;
        }
}
