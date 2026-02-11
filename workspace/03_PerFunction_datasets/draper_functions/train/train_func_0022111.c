dbus_bus_start_service_by_name (DBusConnection *connection,
                                const char     *name,
                                dbus_uint32_t   flags,
                                dbus_uint32_t  *result,
                                DBusError      *error)
{
  DBusMessage *msg;
  DBusMessage *reply;

  _dbus_return_val_if_fail (connection != NULL, FALSE);
  _dbus_return_val_if_fail (_dbus_check_is_valid_bus_name (name), FALSE);

  msg = dbus_message_new_method_call (DBUS_SERVICE_DBUS,
                                      DBUS_PATH_DBUS,
                                      DBUS_INTERFACE_DBUS,
                                      "StartServiceByName");

  if (!dbus_message_append_args (msg, DBUS_TYPE_STRING, &name,
			  	 DBUS_TYPE_UINT32, &flags, DBUS_TYPE_INVALID))
    {
      dbus_message_unref (msg);
      _DBUS_SET_OOM (error);
      return FALSE;
    }

  reply = dbus_connection_send_with_reply_and_block (connection, msg,
                                                     -1, error);
  dbus_message_unref (msg);

  if (reply == NULL)
    {
      _DBUS_ASSERT_ERROR_IS_SET (error);
      return FALSE;
    }

  if (dbus_set_error_from_message (error, reply))
    {
      _DBUS_ASSERT_ERROR_IS_SET (error);
      dbus_message_unref (reply);
      return FALSE;
    }

  if (result != NULL &&
      !dbus_message_get_args (reply, error, DBUS_TYPE_UINT32,
	      		      result, DBUS_TYPE_INVALID))
    {
      _DBUS_ASSERT_ERROR_IS_SET (error);
      dbus_message_unref (reply);
      return FALSE;
    }

  dbus_message_unref (reply);
  return TRUE;
}
