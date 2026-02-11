dbus_message_get_path_decomposed (DBusMessage   *message,
                                  char        ***path)
{
  const char *v;

  _dbus_return_val_if_fail (message != NULL, FALSE);
  _dbus_return_val_if_fail (path != NULL, FALSE);

  *path = NULL;

  v = dbus_message_get_path (message);
  if (v != NULL)
    {
      if (!_dbus_decompose_path (v, strlen (v),
                                 path, NULL))
        return FALSE;
    }
  return TRUE;
}
