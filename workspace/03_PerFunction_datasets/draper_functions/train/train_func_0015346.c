bus_connection_get_apparmor_confinement (DBusConnection *connection)
{
  BusConnectionData *d;

  d = BUS_CONNECTION_DATA (connection);

  _dbus_assert (d != NULL);

  bus_apparmor_confinement_ref (d->apparmor_confinement);
  return d->apparmor_confinement;
}
