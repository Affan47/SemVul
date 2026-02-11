on_object_added (GDBusObjectManager *manager,
                 GDBusObject *object,
                 gpointer user_data)
{
        GList *interfaces, *l;

        interfaces = g_dbus_object_get_interfaces (object);
        for (l = interfaces; l != NULL; l = g_list_next (l))
                on_interface_added (manager, object, l->data);
        g_list_free_full (interfaces, g_object_unref);

        if (is_realm_with_kerberos_and_membership (object)) {
                g_debug ("Saw realm: %s", g_dbus_object_get_object_path (object));
                g_signal_emit (user_data, signals[REALM_ADDED], 0, object);
        }
}
