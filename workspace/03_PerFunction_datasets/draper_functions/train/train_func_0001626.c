live_messages_notify (DBusCounter *counter,
                           void        *user_data)
{
  DBusTransport *transport = user_data;

  _dbus_transport_ref (transport);

#if 0
  _dbus_verbose ("Size counter value is now %d\n",
                 (int) _dbus_counter_get_size_value (counter));
  _dbus_verbose ("Unix FD counter value is now %d\n",
                 (int) _dbus_counter_get_unix_fd_value (counter));
#endif


  if (transport->vtable->live_messages_changed)
    {
      _dbus_connection_lock (transport->connection);
      (* transport->vtable->live_messages_changed) (transport);
      _dbus_connection_unlock (transport->connection);
    }

  _dbus_transport_unref (transport);
}
