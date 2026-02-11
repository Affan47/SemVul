_dbus_connection_get_next_client_serial (DBusConnection *connection)
{
  dbus_uint32_t serial;

  serial = connection->client_serial++;

  if (connection->client_serial == 0)
    connection->client_serial = 1;

  return serial;
}
