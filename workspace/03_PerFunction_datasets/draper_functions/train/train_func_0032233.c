connection_cancel_transaction (DBusConnection *connection,
                               BusTransaction *transaction)
{
  DBusList *link;
  BusConnectionData *d;

  d = BUS_CONNECTION_DATA (connection);
  _dbus_assert (d != NULL);

  link = _dbus_list_get_first_link (&d->transaction_messages);
  while (link != NULL)
    {
      MessageToSend *m = link->data;
      DBusList *next = _dbus_list_get_next_link (&d->transaction_messages, link);

      if (m->transaction == transaction)
        {
          _dbus_list_remove_link (&d->transaction_messages,
                                  link);

          message_to_send_free (connection, m);
        }

      link = next;
    }
}
