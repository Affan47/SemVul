bus_dbus_impl_get_connection_by_name (BusDBusImpl    *dbus,
                                      const gchar    *name)
{
    g_assert (BUS_IS_DBUS_IMPL (dbus));
    g_assert (name != NULL);

    if (G_LIKELY (g_dbus_is_unique_name (name))) {
        return (BusConnection *) g_hash_table_lookup (dbus->unique_names, name);
    }
    else {
        BusNameService *service;
        BusConnectionOwner *owner;

        service = (BusNameService *) g_hash_table_lookup (dbus->names, name);
        if (service == NULL) {
            return NULL;
        }
        owner = bus_name_service_get_primary_owner (service);
        return owner ? owner->conn : NULL;
    }
}
