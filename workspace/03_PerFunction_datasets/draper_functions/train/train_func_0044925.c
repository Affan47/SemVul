_dbus_command_for_pid (unsigned long  pid,
                       DBusString    *str,
                       int            max_len,
                       DBusError     *error)
{

  DBusString path;
  DBusString cmdline;
  int fd;

  if (!_dbus_string_init (&path))
    {
      _DBUS_SET_OOM (error);
      return FALSE;
    }

  if (!_dbus_string_init (&cmdline))
    {
      _DBUS_SET_OOM (error);
      _dbus_string_free (&path);
      return FALSE;
    }

  if (!_dbus_string_append_printf (&path, "/proc/%ld/cmdline", pid))
    goto oom;

  fd = open (_dbus_string_get_const_data (&path), O_RDONLY);
  if (fd < 0)
    {
      dbus_set_error (error,
                      _dbus_error_from_errno (errno),
                      "Failed to open \"%s\": %s",
                      _dbus_string_get_const_data (&path),
                      _dbus_strerror (errno));
      goto fail;
    }

  if (!_dbus_read (fd, &cmdline, max_len))
    {
      dbus_set_error (error,
                      _dbus_error_from_errno (errno),
                      "Failed to read from \"%s\": %s",
                      _dbus_string_get_const_data (&path),
                      _dbus_strerror (errno));
      _dbus_close (fd, NULL);
      goto fail;
    }

  if (!_dbus_close (fd, error))
    goto fail;

  string_squash_nonprintable (&cmdline);

  if (!_dbus_string_copy (&cmdline, 0, str, _dbus_string_get_length (str)))
    goto oom;

  _dbus_string_free (&cmdline);
  _dbus_string_free (&path);
  return TRUE;
oom:
  _DBUS_SET_OOM (error);
fail:
  _dbus_string_free (&cmdline);
  _dbus_string_free (&path);
  return FALSE;
}
