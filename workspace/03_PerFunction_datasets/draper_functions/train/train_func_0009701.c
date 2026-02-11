init_system_db (void)
{
  _dbus_assert (database_locked);

  if (system_db == NULL)
    {
      DBusError error = DBUS_ERROR_INIT;
      const DBusUserInfo *info;

      system_db = _dbus_user_database_new ();
      if (system_db == NULL)
        return FALSE;

      if (!_dbus_user_database_get_uid (system_db,
                                        _dbus_getuid (),
                                        &info,
                                        &error))
        {
          _dbus_user_database_unref (system_db);
          system_db = NULL;

          if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY))
            {
              dbus_error_free (&error);
              return FALSE;
            }
          else
            {

              _dbus_warn ("Could not get password database information for UID of current process: %s\n",
                          error.message);
              dbus_error_free (&error);
              return FALSE;
            }
        }

      if (!_dbus_string_init (&process_username))
        {
          _dbus_user_database_unref (system_db);
          system_db = NULL;
          return FALSE;
        }

      if (!_dbus_string_init (&process_homedir))
        {
          _dbus_string_free (&process_username);
          _dbus_user_database_unref (system_db);
          system_db = NULL;
          return FALSE;
        }

      if (!_dbus_string_append (&process_username,
                                info->username) ||
          !_dbus_string_append (&process_homedir,
                                info->homedir) ||
          !_dbus_register_shutdown_func (shutdown_system_db, NULL))
        {
          _dbus_string_free (&process_username);
          _dbus_string_free (&process_homedir);
          _dbus_user_database_unref (system_db);
          system_db = NULL;
          return FALSE;
        }
    }

  return TRUE;
}
