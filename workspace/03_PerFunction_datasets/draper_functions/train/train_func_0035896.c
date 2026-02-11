gdm_dbus_get_pid_for_name (const char  *system_bus_name,
                           pid_t       *out_pid,
                           GError     **error)
{
        GDBusConnection *bus;
        GVariant *reply;
        gboolean retval = FALSE;
        unsigned int v;

        bus = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, error);
        if (bus == NULL) {
                return FALSE;
        }

        reply = g_dbus_connection_call_sync (bus,
                                             "org.freedesktop.DBus",
                                             "/org/freedesktop/DBus",
                                             "org.freedesktop.DBus",
                                             "GetConnectionUnixProcessID",
                                             g_variant_new ("(s)", system_bus_name),
                                             G_VARIANT_TYPE ("(u)"),
                                             G_DBUS_CALL_FLAGS_NONE,
                                             -1,
                                             NULL, error);
        if (reply == NULL) {
                goto out;
        }

        g_variant_get (reply, "(u)", &v);
        *out_pid = v;
        g_variant_unref (reply);

        retval = TRUE;
 out:
        g_object_unref (bus);

        return retval;
}
