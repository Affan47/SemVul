e_dbus_connection_data_watch_add(E_DBus_Connection *cd, DBusWatch *watch)
{
  E_DBus_Handler_Data *hd;

  hd = calloc(1, sizeof(E_DBus_Handler_Data));
  dbus_watch_set_data(watch, hd, e_dbus_handler_data_free);
  hd->cd = cd;
  hd->watch = watch;

  hd->enabled = dbus_watch_get_enabled(watch);
#if (DBUS_VERSION_MAJOR == 1 && DBUS_VERSION_MINOR == 1 && DBUS_VERSION_MICRO>= 1) || (DBUS_VERSION_MAJOR == 1 && DBUS_VERSION_MINOR > 1) || (DBUS_VERSION_MAJOR > 1)
  hd->fd = dbus_watch_get_unix_fd(hd->watch);
#else
  hd->fd = dbus_watch_get_fd(hd->watch);
#endif
  DBG("watch add (enabled: %d)", hd->enabled);
  if (hd->enabled) e_dbus_fd_handler_add(hd);
}
