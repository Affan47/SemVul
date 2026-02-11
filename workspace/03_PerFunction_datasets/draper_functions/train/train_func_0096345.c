ibus_bus_is_connected (IBusBus *bus)
{
    g_return_val_if_fail (IBUS_IS_BUS (bus), FALSE);

    if (bus->priv->connection == NULL || g_dbus_connection_is_closed (bus->priv->connection))
        return FALSE;

    return TRUE;
}
