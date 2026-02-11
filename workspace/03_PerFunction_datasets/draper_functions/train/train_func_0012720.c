_dbus_user_at_console (const char *username,
                       DBusError  *error)
{

  DBusString u, f;
  dbus_bool_t result;

  result = FALSE;
  if (!_dbus_string_init (&f))
    {
      _DBUS_SET_OOM (error);
      return FALSE;
    }

  if (!_dbus_string_append (&f, DBUS_CONSOLE_AUTH_DIR))
    {
      _DBUS_SET_OOM (error);
      goto out;
    }

  _dbus_string_init_const (&u, username);

  if (!_dbus_concat_dir_and_file (&f, &u))
    {
      _DBUS_SET_OOM (error);
      goto out;
    }

  result = _dbus_file_exists (_dbus_string_get_const_data (&f));

 out:
  _dbus_string_free (&f);

  return result;
}
