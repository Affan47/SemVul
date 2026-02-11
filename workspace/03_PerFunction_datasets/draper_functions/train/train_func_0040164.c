_dbus_keyring_lock (DBusKeyring *keyring)
{
  int n_timeouts;

  n_timeouts = 0;
  while (n_timeouts < MAX_LOCK_TIMEOUTS)
    {
      DBusError error = DBUS_ERROR_INIT;

      if (_dbus_create_file_exclusively (&keyring->filename_lock,
                                         &error))
        break;

      _dbus_verbose ("Did not get lock file, sleeping %d milliseconds (%s)\n",
                     LOCK_TIMEOUT_MILLISECONDS, error.message);
      dbus_error_free (&error);

      _dbus_sleep_milliseconds (LOCK_TIMEOUT_MILLISECONDS);

      ++n_timeouts;
    }

  if (n_timeouts == MAX_LOCK_TIMEOUTS)
    {
      DBusError error = DBUS_ERROR_INIT;

      _dbus_verbose ("Lock file timed out %d times, assuming stale\n",
                     n_timeouts);

      if (!_dbus_delete_file (&keyring->filename_lock, &error))
        {
          _dbus_verbose ("Couldn't delete old lock file: %s\n",
                         error.message);
          dbus_error_free (&error);
          return FALSE;
        }

      if (!_dbus_create_file_exclusively (&keyring->filename_lock,
                                          &error))
        {
          _dbus_verbose ("Couldn't create lock file after deleting stale one: %s\n",
                         error.message);
          dbus_error_free (&error);
          return FALSE;
        }
    }

  return TRUE;
}
