impl_GetState (DBusConnection * bus, DBusMessage * message, void *user_data)
{
  DBusMessage *reply = NULL;
  DBusMessageIter iter, iter_array;

  dbus_uint32_t states[2] = {0, 0};
  guint count;

  reply = dbus_message_new_method_return (message);
  dbus_message_iter_init_append (reply, &iter);

  dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "u", &iter_array);
  for (count = 0; count < 2; count++)
    {
      dbus_message_iter_append_basic (&iter_array, DBUS_TYPE_UINT32,
                                      &states[count]);
    }
  dbus_message_iter_close_container (&iter, &iter_array);
  return reply;
}
