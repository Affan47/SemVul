get_filename_for_profile_path (DBusConnection *con,
                               const char *object_path)
{
  char *filename = NULL;
  const char *interface = "org.freedesktop.ColorManager.Profile";
  const char *property = "Filename";
  const char *tmp;
  DBusError error;
  DBusMessageIter args;
  DBusMessage *message = NULL;
  DBusMessage *reply = NULL;
  DBusMessageIter sub;

  message = dbus_message_new_method_call("org.freedesktop.ColorManager",
                 object_path,
                 "org.freedesktop.DBus.Properties",
                 "Get");

  dbus_message_iter_init_append(message, &args);
  dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &interface);
  dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &property);


  dbus_error_init(&error);
  fprintf(stderr, "DEBUG: Calling %s.Get(%s)\n", interface, property);
  reply = dbus_connection_send_with_reply_and_block(con,
                message,
                -1,
                &error);
  if (reply == NULL) {
    fprintf(stderr, "DEBUG: Failed to send: %s:%s\n",
           error.name, error.message);
    dbus_error_free(&error);
    goto out;
  }


  dbus_message_iter_init(reply, &args);
  if (dbus_message_iter_get_arg_type(&args) != DBUS_TYPE_VARIANT) {
    fprintf(stderr, "DEBUG: Incorrect reply type\n");
    goto out;
  }

  dbus_message_iter_recurse(&args, &sub);
  dbus_message_iter_get_basic(&sub, &tmp);
  filename = strdup(tmp);
out:
  if (message != NULL)
    dbus_message_unref(message);
  if (reply != NULL)
    dbus_message_unref(reply);
  return filename;
}
