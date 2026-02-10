_dbus_string_append_byte_as_hex (DBusString *str,
                                 unsigned char byte)
{
  const char hexdigits[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'a', 'b', 'c', 'd', 'e', 'f'
  };

  if (!_dbus_string_append_byte (str,
                                 hexdigits[(byte >> 4)]))
    return FALSE;

  if (!_dbus_string_append_byte (str,
                                 hexdigits[(byte & 0x0f)]))
    {
      _dbus_string_set_length (str,
                               _dbus_string_get_length (str) - 1);
      return FALSE;
    }

  return TRUE;
}
