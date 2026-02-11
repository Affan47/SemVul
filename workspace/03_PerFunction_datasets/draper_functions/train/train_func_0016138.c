bus_connection_remove_transactions (DBusConnection *connection)
{
  MessageToSend *to_send;
  BusConnectionData *d;

  d = BUS_CONNECTION_DATA (connection);
  _dbus_assert (d != NULL);

  while ((to_send = _dbus_list_get_first (&d->transaction_messages)))
    {

      _dbus_list_remove (&to_send->transaction->connections,
                         connection);

      _dbus_list_remove (&d->transaction_messages, to_send);
      message_to_send_free (connection, to_send);
    }
}
