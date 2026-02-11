dbus_connection_steal_borrowed_message (DBusConnection *connection,
					DBusMessage    *message)
{
  DBusMessage *pop_message;
  DBusDispatchStatus status;

  _dbus_return_if_fail (connection != NULL);
  _dbus_return_if_fail (message != NULL);
  _dbus_return_if_fail (message == connection->message_borrowed);
  _dbus_return_if_fail (connection->dispatch_acquired);

  CONNECTION_LOCK (connection);

  _dbus_assert (message == connection->message_borrowed);

  pop_message = _dbus_list_pop_first (&connection->incoming_messages);
  _dbus_assert (message == pop_message);
  (void) pop_message;

  connection->n_incoming -= 1;

  _dbus_verbose ("Incoming message %p stolen from queue, %d incoming\n",
		 message, connection->n_incoming);

  connection->message_borrowed = NULL;

  _dbus_connection_release_dispatch (connection);

  status = _dbus_connection_get_dispatch_status_unlocked (connection);
  _dbus_connection_update_dispatch_status_and_unlock (connection, status);
  _dbus_message_trace_ref (message, -1, -1,
      "dbus_connection_steal_borrowed_message");
}
