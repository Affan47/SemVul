dbus_connection_send_preallocated (DBusConnection       *connection,
                                   DBusPreallocatedSend *preallocated,
                                   DBusMessage          *message,
                                   dbus_uint32_t        *client_serial)
{
  _dbus_return_if_fail (connection != NULL);
  _dbus_return_if_fail (preallocated != NULL);
  _dbus_return_if_fail (message != NULL);
  _dbus_return_if_fail (preallocated->connection == connection);
  _dbus_return_if_fail (dbus_message_get_type (message) != DBUS_MESSAGE_TYPE_METHOD_CALL ||
                        dbus_message_get_member (message) != NULL);
  _dbus_return_if_fail (dbus_message_get_type (message) != DBUS_MESSAGE_TYPE_SIGNAL ||
                        (dbus_message_get_interface (message) != NULL &&
                         dbus_message_get_member (message) != NULL));

  CONNECTION_LOCK (connection);

#ifdef HAVE_UNIX_FD_PASSING

  if (!_dbus_transport_can_pass_unix_fd(connection->transport) &&
      message->n_unix_fds > 0)
    {


      CONNECTION_UNLOCK (connection);
      return;
    }

#endif

  _dbus_connection_send_preallocated_and_unlock (connection,
						 preallocated,
						 message, client_serial);
}
