generate_local_error_message (dbus_uint32_t serial,
                              char *error_name,
                              char *error_msg)
{
  DBusMessage *message;
  message = dbus_message_new (DBUS_MESSAGE_TYPE_ERROR);
  if (!message)
    goto out;

  if (!dbus_message_set_error_name (message, error_name))
    {
      dbus_message_unref (message);
      message = NULL;
      goto out;
    }

  dbus_message_set_no_reply (message, TRUE);

  if (!dbus_message_set_reply_serial (message,
                                      serial))
    {
      dbus_message_unref (message);
      message = NULL;
      goto out;
    }

  if (error_msg != NULL)
    {
      DBusMessageIter iter;

      dbus_message_iter_init_append (message, &iter);
      if (!dbus_message_iter_append_basic (&iter,
                                           DBUS_TYPE_STRING,
                                           &error_msg))
        {
          dbus_message_unref (message);
          message = NULL;
	  goto out;
        }
    }

 out:
  return message;
}
