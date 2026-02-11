_dbus_string_chop_white(DBusString *str)
{
  int i;

  _dbus_string_skip_white (str, 0, &i);

  if (i > 0)
    _dbus_string_delete (str, 0, i);

  _dbus_string_skip_white_reverse (str, _dbus_string_get_length (str), &i);

  _dbus_string_set_length (str, i);
}
