_dbus_string_find_to (const DBusString *str,
		      int               start,
		      int               end,
		      const char       *substr,
		      int              *found)
{
  int i;
  DBUS_CONST_STRING_PREAMBLE (str);
  _dbus_assert (substr != NULL);
  _dbus_assert (start <= real->len);
  _dbus_assert (start >= 0);
  _dbus_assert (substr != NULL);
  _dbus_assert (end <= real->len);
  _dbus_assert (start <= end);


  if (*substr == '\0')
    {
      if (found)
        *found = start;
      return TRUE;
    }

  i = start;
  while (i < end)
    {
      if (real->str[i] == substr[0])
        {
          int j = i + 1;

          while (j < end)
            {
              if (substr[j - i] == '\0')
                break;
              else if (real->str[j] != substr[j - i])
                break;

              ++j;
            }

          if (substr[j - i] == '\0')
            {
              if (found)
                *found = i;
              return TRUE;
            }
        }

      ++i;
    }

  if (found)
    *found = end;

  return FALSE;
}
