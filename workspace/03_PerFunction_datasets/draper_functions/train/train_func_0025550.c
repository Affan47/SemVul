check_disconnected_message_arrived_unlocked (DBusConnection *connection,
                                             DBusMessage    *head_of_queue)
{
  HAVE_LOCK_CHECK (connection);


  if (connection->disconnect_message_link == NULL &&
      dbus_message_is_signal (head_of_queue,
                              DBUS_INTERFACE_LOCAL,
                              "Disconnected"))
    {
      connection->disconnected_message_arrived = TRUE;
    }
}
