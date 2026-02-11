handle_get_items (DBusPendingCall *pending, void *user_data)
{
  DBusMessage *reply = dbus_pending_call_steal_reply (pending);
  DBusMessageIter iter, iter_array;

  if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR)
  {
    const char *sender = dbus_message_get_sender (reply);
    const char *error = NULL;
    dbus_message_get_args (reply, NULL, DBUS_TYPE_STRING, &error,
                           DBUS_TYPE_INVALID);
    g_warning ("AT-SPI: Error in GetItems, sender=%s, error=%s", sender, error);
    dbus_message_unref (reply);
    dbus_pending_call_unref (pending);
    return;
  }

  dbus_message_iter_init (reply, &iter);
  dbus_message_iter_recurse (&iter, &iter_array);
  while (dbus_message_iter_get_arg_type (&iter_array) != DBUS_TYPE_INVALID)
  {
    add_accessible_from_iter (&iter_array);
    dbus_message_iter_next (&iter_array);
  }
  dbus_message_unref (reply);
  dbus_pending_call_unref (pending);
}
