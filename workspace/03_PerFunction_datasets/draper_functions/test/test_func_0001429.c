_atspi_dbus_set_interfaces (AtspiAccessible *accessible, DBusMessageIter *iter)
{
  DBusMessageIter iter_array;

  accessible->interfaces = 0;
  dbus_message_iter_recurse (iter, &iter_array);
  while (dbus_message_iter_get_arg_type (&iter_array) != DBUS_TYPE_INVALID)
  {
    const char *iface;
    gint n;
    dbus_message_iter_get_basic (&iter_array, &iface);
    if (!strcmp (iface, "org.freedesktop.DBus.Introspectable")) continue;
    n = _atspi_get_iface_num (iface);
    if (n == -1)
    {
      g_warning ("AT-SPI: Unknown interface %s", iface);
    }
    else
      accessible->interfaces |= (1 << n);
    dbus_message_iter_next (&iter_array);
  }
  _atspi_accessible_add_cache (accessible, ATSPI_CACHE_INTERFACES);
}
