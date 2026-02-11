impl_SetPosition (DBusConnection * bus, DBusMessage * message, void *user_data)
{
  AtkComponent *component = (AtkComponent *) user_data;
  dbus_uint32_t coord_type;
  dbus_int32_t x, y;
  dbus_bool_t ret;
  DBusMessage *reply;

  g_return_val_if_fail (ATK_IS_COMPONENT (user_data),
                        droute_not_yet_handled_error (message));

  if (!dbus_message_get_args
      (message, NULL, DBUS_TYPE_INT32, &x, DBUS_TYPE_INT32, &y,
       DBUS_TYPE_UINT32, &coord_type, DBUS_TYPE_INVALID))
    {
      return droute_invalid_arguments_error (message);
    }

  ret = atk_component_set_position (component, x, y, coord_type);

  reply = dbus_message_new_method_return (message);
  if (reply)
    {
      dbus_message_append_args (reply, DBUS_TYPE_BOOLEAN, &ret,
                                DBUS_TYPE_INVALID);
    }

  return reply;
}
