_dbus_connection_send_preallocated_unlocked_no_update (DBusConnection       *connection,
                                                       DBusPreallocatedSend *preallocated,
                                                       DBusMessage          *message,
                                                       dbus_uint32_t        *client_serial)
{
  dbus_uint32_t serial;

  preallocated->queue_link->data = message;
  _dbus_list_prepend_link (&connection->outgoing_messages,
                           preallocated->queue_link);


  _dbus_message_add_counter_link (message,
                                  preallocated->counter_link);

  dbus_free (preallocated);
  preallocated = NULL;

  dbus_message_ref (message);

  connection->n_outgoing += 1;

  _dbus_verbose ("Message %p (%s %s %s %s '%s') for %s added to outgoing queue %p, %d pending to send\n",
                 message,
                 dbus_message_type_to_string (dbus_message_get_type (message)),
                 dbus_message_get_path (message) ?
                 dbus_message_get_path (message) :
                 "no path",
                 dbus_message_get_interface (message) ?
                 dbus_message_get_interface (message) :
                 "no interface",
                 dbus_message_get_member (message) ?
                 dbus_message_get_member (message) :
                 "no member",
                 dbus_message_get_signature (message),
                 dbus_message_get_destination (message) ?
                 dbus_message_get_destination (message) :
                 "null",
                 connection,
                 connection->n_outgoing);

  if (dbus_message_get_serial (message) == 0)
    {
      serial = _dbus_connection_get_next_client_serial (connection);
      dbus_message_set_serial (message, serial);
      if (client_serial)
        *client_serial = serial;
    }
  else
    {
      if (client_serial)
        *client_serial = dbus_message_get_serial (message);
    }

  _dbus_verbose ("Message %p serial is %u\n",
                 message, dbus_message_get_serial (message));

  dbus_message_lock (message);


  _dbus_connection_do_iteration_unlocked (connection,
                                          NULL,
                                          DBUS_ITERATION_DO_WRITING,
                                          -1);


  if (connection->n_outgoing > 0)
    _dbus_connection_wakeup_mainloop (connection);
}
