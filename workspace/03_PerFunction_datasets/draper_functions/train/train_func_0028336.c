print_services (DBusConnection *connection)
{
  DBusMessage *message;
  DBusMessage *reply;
  DBusError error;
  DBusMessageIter iter;
  DBusMessageIter iter_array;
  const char *name;


  message = dbus_message_new_method_call (DBUS_SERVICE_DBUS,
                                          DBUS_PATH_DBUS,
                                          DBUS_INTERFACE_DBUS,
                                          "ListNames");
  dbus_error_init (&error);
  reply = dbus_connection_send_with_reply_and_block (connection,
                                                     message,
                                                     -1,
                                                     &error);
  dbus_message_unref (message);
  dbus_message_iter_init (reply, &iter);
  dbus_message_iter_recurse (&iter, &iter_array);
  while (dbus_message_iter_get_arg_type (&iter_array) != DBUS_TYPE_INVALID)
    {
      dbus_message_iter_get_basic (&iter_array, &name);
      if (name[0] != ':')
        printf ("%s \n", name);
      dbus_message_iter_next (&iter_array);
    }
  dbus_message_unref (reply);

  message = dbus_message_new_method_call (DBUS_SERVICE_DBUS,
                                          DBUS_PATH_DBUS,
                                          DBUS_INTERFACE_DBUS,
                                          "ListActivatableNames");
  dbus_error_init (&error);
  reply = dbus_connection_send_with_reply_and_block (connection,
                                                     message,
                                                     -1,
                                                     &error);
  dbus_message_unref (message);
  dbus_message_iter_init (reply, &iter);
  dbus_message_iter_recurse (&iter, &iter_array);
  while (dbus_message_iter_get_arg_type (&iter_array) != DBUS_TYPE_INVALID)
    {
      dbus_message_iter_get_basic (&iter_array, &name);
      printf ("%s \n", name);
      dbus_message_iter_next (&iter_array);
    }
  dbus_message_unref (reply);
}
