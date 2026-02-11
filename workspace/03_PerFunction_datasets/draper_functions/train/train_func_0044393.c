dbus_connection_send (DBusConnection *connection,
                      DBusMessage    *message,
                      dbus_uint32_t  *serial)
{
  _dbus_return_val_if_fail (connection != NULL, FALSE);
  _dbus_return_val_if_fail (message != NULL, FALSE);

  CONNECTION_LOCK (connection);

#ifdef HAVE_UNIX_FD_PASSING

  if (!_dbus_transport_can_pass_unix_fd(connection->transport) &&
      message->n_unix_fds > 0)
    {


      CONNECTION_UNLOCK (connection);
      return FALSE;
    }

#endif

  return _dbus_connection_send_and_unlock (connection,
					   message,
					   serial);
}
