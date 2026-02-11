_dbus_string_validate_ascii (const DBusString *str,
                             int               start,
                             int               len)
{
  const unsigned char *s;
  const unsigned char *end;
  DBUS_CONST_STRING_PREAMBLE (str);
  _dbus_assert (start >= 0);
  _dbus_assert (start <= real->len);
  _dbus_assert (len >= 0);

  if (len > real->len - start)
    return FALSE;

  s = real->str + start;
  end = s + len;
  while (s != end)
    {
      if (_DBUS_UNLIKELY (!_DBUS_ISASCII (*s)))
        return FALSE;

      ++s;
    }

  return TRUE;
}
