_dbus_get_autolaunch_address (const char *scope,
                              DBusString *address,
                              DBusError  *error)
{
#ifdef DBUS_ENABLE_X11_AUTOLAUNCH


  const char *display;
  static char *argv[6];
  int i;
  DBusString uuid;
  dbus_bool_t retval;

  if (_dbus_check_setuid ())
    {
      dbus_set_error_const (error, DBUS_ERROR_NOT_SUPPORTED,
                            "Unable to autolaunch when setuid");
      return FALSE;
    }

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  retval = FALSE;


  display = _dbus_getenv ("DISPLAY");

  if (display == NULL || display[0] == '\0')
    {
      dbus_set_error_const (error, DBUS_ERROR_NOT_SUPPORTED,
          "Unable to autolaunch a dbus-daemon without a $DISPLAY for X11");
      return FALSE;
    }

  if (!_dbus_string_init (&uuid))
    {
      _DBUS_SET_OOM (error);
      return FALSE;
    }

  if (!_dbus_get_local_machine_uuid_encoded (&uuid))
    {
      _DBUS_SET_OOM (error);
      goto out;
    }

  i = 0;
  argv[i] = "dbus-launch";
  ++i;
  argv[i] = "--autolaunch";
  ++i;
  argv[i] = _dbus_string_get_data (&uuid);
  ++i;
  argv[i] = "--binary-syntax";
  ++i;
  argv[i] = "--close-stderr";
  ++i;
  argv[i] = NULL;
  ++i;

  _dbus_assert (i == _DBUS_N_ELEMENTS (argv));

  retval = _read_subprocess_line_argv (DBUS_BINDIR "/dbus-launch",
                                       TRUE,
                                       argv, address, error);

 out:
  _dbus_string_free (&uuid);
  return retval;
#else
  dbus_set_error_const (error, DBUS_ERROR_NOT_SUPPORTED,
      "Using X11 for dbus-daemon autolaunch was disabled at compile time, "
      "set your DBUS_SESSION_BUS_ADDRESS instead");
  return FALSE;
#endif
}
