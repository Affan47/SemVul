_dbus_connection_do_iteration_unlocked (DBusConnection *connection,
                                        DBusPendingCall *pending,
                                        unsigned int    flags,
                                        int             timeout_milliseconds)
{
  _dbus_verbose ("start\n");

  HAVE_LOCK_CHECK (connection);

  if (connection->n_outgoing == 0)
    flags &= ~DBUS_ITERATION_DO_WRITING;

  if (_dbus_connection_acquire_io_path (connection,
					(flags & DBUS_ITERATION_BLOCK) ? timeout_milliseconds : 0))
    {
      HAVE_LOCK_CHECK (connection);

      if ( (pending != NULL) && _dbus_pending_call_get_completed_unlocked(pending))
        {
          _dbus_verbose ("pending call completed while acquiring I/O path");
        }
      else if ( (pending != NULL) &&
                _dbus_connection_peek_for_reply_unlocked (connection,
                                                          _dbus_pending_call_get_reply_serial_unlocked (pending)))
        {
          _dbus_verbose ("pending call completed while acquiring I/O path (reply found in queue)");
        }
      else
        {
          _dbus_transport_do_iteration (connection->transport,
                                        flags, timeout_milliseconds);
        }

      _dbus_connection_release_io_path (connection);
    }

  HAVE_LOCK_CHECK (connection);

  _dbus_verbose ("end\n");
}
