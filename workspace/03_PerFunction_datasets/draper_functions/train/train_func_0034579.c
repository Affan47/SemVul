impl_GetChildAtIndex (DBusConnection * bus,
                      DBusMessage * message, void *user_data)
{
  SpiRegistry *reg = SPI_REGISTRY (user_data);
  DBusMessage *reply;
  DBusMessageIter iter;
  DBusError error;
  SpiReference *ref;
  dbus_int32_t i;

  dbus_error_init (&error);
  if (!dbus_message_get_args
       (message, &error, DBUS_TYPE_INT32, &i, DBUS_TYPE_INVALID))
    {
      return dbus_message_new_error (message, DBUS_ERROR_FAILED, "Invalid arguments");
    }

  reply = dbus_message_new_method_return (message);
  dbus_message_iter_init_append (reply, &iter);

  if (i < 0 || i >= reg->apps->len)
    append_reference (&iter, SPI_DBUS_NAME_REGISTRY, SPI_DBUS_PATH_NULL);
  else
    {
      ref = g_ptr_array_index (reg->apps, i);
      append_reference (&iter, ref->name, ref->path);
    }

  return reply;
}
