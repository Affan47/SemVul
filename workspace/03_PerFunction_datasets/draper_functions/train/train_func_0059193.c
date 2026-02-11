_dbus_string_init_const_len (DBusString *str,
                             const char *value,
                             int         len)
{
  DBusRealString *real;

  _dbus_assert (str != NULL);
  _dbus_assert (len == 0 || value != NULL);
  _dbus_assert (len <= _DBUS_STRING_MAX_LENGTH);
  _dbus_assert (len >= 0);

  real = (DBusRealString*) str;

  real->str = (unsigned char*) value;
  real->len = len;
  real->allocated = real->len + _DBUS_STRING_ALLOCATION_PADDING;
  real->constant = TRUE;
  real->locked = TRUE;
  real->invalid = FALSE;
  real->align_offset = 0;


}
