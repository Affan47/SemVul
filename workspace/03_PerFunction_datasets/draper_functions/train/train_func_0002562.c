_dbus_connection_get_dispatch_status_unlocked (DBusConnection *connection)
{
  HAVE_LOCK_CHECK (connection);

  if (connection->n_incoming > 0)
    return DBUS_DISPATCH_DATA_REMAINS;
  else if (!_dbus_transport_queue_messages (connection->transport))
    return DBUS_DISPATCH_NEED_MEMORY;
  else
    {
      DBusDispatchStatus status;
      dbus_bool_t is_connected;

      status = _dbus_transport_get_dispatch_status (connection->transport);
      is_connected = _dbus_transport_get_is_connected (connection->transport);

      _dbus_verbose ("dispatch status = %s is_connected = %d\n",
                     DISPATCH_STATUS_NAME (status), is_connected);

      if (!is_connected)
        {


          notify_disconnected_unlocked (connection);


          if (status == DBUS_DISPATCH_COMPLETE)
            status = notify_disconnected_and_dispatch_complete_unlocked (connection);
        }

      if (status != DBUS_DISPATCH_COMPLETE)
        return status;
      else if (connection->n_incoming > 0)
        return DBUS_DISPATCH_DATA_REMAINS;
      else
        return DBUS_DISPATCH_COMPLETE;
    }
}
