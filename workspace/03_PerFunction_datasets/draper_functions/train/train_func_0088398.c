ibus_bus_add_match (IBusBus     *bus,
                    const gchar *rule)
{
    g_return_val_if_fail (IBUS_IS_BUS (bus), FALSE);
    g_return_val_if_fail (rule != NULL, FALSE);

    GVariant *result;
    result = ibus_bus_call_sync (bus,
                                 DBUS_SERVICE_DBUS,
                                 DBUS_PATH_DBUS,
                                 DBUS_INTERFACE_DBUS,
                                 "AddMatch",
                                 g_variant_new ("(s)", rule),
                                 NULL);

    if (result) {
        g_variant_unref (result);
        return TRUE;
    }
    return FALSE;
}
