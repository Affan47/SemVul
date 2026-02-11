impl_GetText (DBusConnection * bus, DBusMessage * message, void *user_data)
{
  AtkText *text = (AtkText *) user_data;
  dbus_int32_t startOffset, endOffset;
  gchar *txt;
  DBusMessage *reply;

  g_return_val_if_fail (ATK_IS_TEXT (user_data),
                        droute_not_yet_handled_error (message));
  if (!dbus_message_get_args
      (message, NULL, DBUS_TYPE_INT32, &startOffset, DBUS_TYPE_INT32,
       &endOffset, DBUS_TYPE_INVALID))
    {
      return droute_invalid_arguments_error (message);
    }
  txt = atk_text_get_text (text, startOffset, endOffset);
  txt = validate_allocated_string (txt);
  reply = dbus_message_new_method_return (message);
  if (reply)
    {
      dbus_message_append_args (reply, DBUS_TYPE_STRING, &txt,
                                DBUS_TYPE_INVALID);
    }
  g_free (txt);
  return reply;
}
