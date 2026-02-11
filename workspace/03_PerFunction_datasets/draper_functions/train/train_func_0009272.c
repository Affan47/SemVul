connection_execute_transaction (DBusConnection *connection,
                                BusTransaction *transaction)
{
  DBusList *link;
  BusConnectionData *d;

  d = BUS_CONNECTION_DATA (connection);
  _dbus_assert (d != NULL);


  link = _dbus_list_get_last_link (&d->transaction_messages);
  while (link != NULL)
    {
      MessageToSend *m = link->data;
      DBusList *prev = _dbus_list_get_prev_link (&d->transaction_messages, link);

      if (m->transaction == transaction)
        {
          _dbus_list_remove_link (&d->transaction_messages,
                                  link);

          _dbus_assert (dbus_message_get_sender (m->message) != NULL);

          dbus_connection_send_preallocated (connection,
                                             m->preallocated,
                                             m->message,
                                             NULL);

          m->preallocated = NULL;

          message_to_send_free (connection, m);
        }

      link = prev;
    }
}
