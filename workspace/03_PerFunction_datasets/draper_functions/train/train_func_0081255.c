_dbus_credentials_add_windows_sid (DBusCredentials    *credentials,
                                   const char         *windows_sid)
{
  char *copy;

  copy = _dbus_strdup (windows_sid);
  if (copy == NULL)
    return FALSE;

  dbus_free (credentials->windows_sid);
  credentials->windows_sid = copy;

  return TRUE;
}
