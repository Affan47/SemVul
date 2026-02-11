impl_SetExtents (DBusConnection * bus, DBusMessage * message, void *user_data)
{
  AtkComponent *component = (AtkComponent *) user_data;
  DBusMessageIter iter, iter_struct;
  dbus_uint32_t coord_type;
  dbus_int32_t x, y, width, height;
  dbus_bool_t ret;
  DBusMessage *reply;

  g_return_val_if_fail (ATK_IS_COMPONENT (user_data),
                        droute_not_yet_handled_error (message));

  if (strcmp (dbus_message_get_signature (message), "(iiii)u") != 0)
    {
      return droute_invalid_arguments_error (message);
    }

  dbus_message_iter_init (message, &iter);
  dbus_message_iter_recurse (&iter, &iter_struct);
  dbus_message_iter_get_basic (&iter_struct, &x);
  dbus_message_iter_next (&iter_struct);
  dbus_message_iter_get_basic (&iter_struct, &y);
  dbus_message_iter_next (&iter_struct);
  dbus_message_iter_get_basic (&iter_struct, &width);
  dbus_message_iter_next (&iter_struct);
  dbus_message_iter_get_basic (&iter_struct, &height);
  dbus_message_iter_next (&iter_struct);
  dbus_message_iter_next (&iter);
  dbus_message_iter_get_basic (&iter, &coord_type);

  ret = atk_component_set_extents (component, x, y, width, height, coord_type);

  reply = dbus_message_new_method_return (message);
  if (reply)
    {
      dbus_message_append_args (reply, DBUS_TYPE_BOOLEAN, &ret,
                                DBUS_TYPE_INVALID);
    }

  return reply;
}
