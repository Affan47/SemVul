handle_device_listener_registered (DBusConnection *bus, DBusMessage *message,
                                    void *user_data)
{
  char *sender;
  DBusMessageIter iter, iter_struct;

  if (strncmp (dbus_message_get_signature (message), "(s", 2) != 0)
    {
      g_warning ("atk-bridge: handle_device_listener_register: unknown signature");
      return;
    }

  dbus_message_iter_init (message, &iter);
  dbus_message_iter_recurse (&iter, &iter_struct);
  dbus_message_iter_get_basic (&iter_struct, &sender);
  spi_atk_add_client (sender);
}
