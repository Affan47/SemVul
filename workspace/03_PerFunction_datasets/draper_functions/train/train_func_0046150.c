append_entry (gpointer key, gpointer val, gpointer data)
{
  DBusMessageIter *iter = data;
  DBusMessageIter iter_entry;

  if (!dbus_message_iter_open_container (iter, DBUS_TYPE_DICT_ENTRY, NULL,
                                        &iter_entry))
    return;
  dbus_message_iter_append_basic (&iter_entry, DBUS_TYPE_STRING, &key);
  dbus_message_iter_append_basic (&iter_entry, DBUS_TYPE_STRING, &val);
  dbus_message_iter_close_container (iter, &iter_entry);
}
