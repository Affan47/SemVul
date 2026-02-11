_connection_dbus_signal_cb (GDBusConnection *connection,
                            const gchar *sender_name,
                            const gchar *object_path,
                            const gchar *interface_name,
                            const gchar *signal_name,
                            GVariant *parameters,
                            gpointer user_data)
{
    g_return_if_fail (user_data != NULL);
    g_return_if_fail (IBUS_IS_BUS (user_data));

    if (g_strcmp0 (signal_name, "NameOwnerChanged") == 0) {
        gchar *name = NULL;
        gchar *old_owner = NULL;
        gchar *new_owner = NULL;
        g_variant_get (parameters, "(&s&s&s)", &name, &old_owner, &new_owner);
        g_signal_emit (IBUS_BUS (user_data),
                       bus_signals[NAME_OWNER_CHANGED], 0,
                       name, old_owner, new_owner);
    }

}
