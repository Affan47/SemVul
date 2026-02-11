bus_driver_handle_get_adt_audit_session_data (DBusConnection *connection,
					      BusTransaction *transaction,
					      DBusMessage    *message,
					      DBusError      *error)
{
  const char *service;
  DBusString str;
  BusRegistry *registry;
  BusService *serv;
  DBusConnection *conn;
  DBusMessage *reply;
  void *data = NULL;
  dbus_uint32_t data_size;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  registry = bus_connection_get_registry (connection);

  service = NULL;
  reply = NULL;

  if (! dbus_message_get_args (message, error,
			       DBUS_TYPE_STRING, &service,
			       DBUS_TYPE_INVALID))
      goto failed;

  _dbus_verbose ("asked for audit session data for connection %s\n", service);

  _dbus_string_init_const (&str, service);
  serv = bus_registry_lookup (registry, &str);
  if (serv == NULL)
    {
      dbus_set_error (error,
		      DBUS_ERROR_NAME_HAS_NO_OWNER,
		      "Could not get audit session data for name '%s': no such name", service);
      goto failed;
    }

  conn = bus_service_get_primary_owners_connection (serv);

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    goto oom;

  if (!dbus_connection_get_adt_audit_session_data (conn, &data, &data_size) || data == NULL)
    {
      dbus_set_error (error,
                      DBUS_ERROR_ADT_AUDIT_DATA_UNKNOWN,
                      "Could not determine audit session data for '%s'", service);
      goto failed;
    }

  if (! dbus_message_append_args (reply,
                                  DBUS_TYPE_ARRAY, DBUS_TYPE_BYTE, &data, data_size,
                                  DBUS_TYPE_INVALID))
    goto oom;

  if (! bus_transaction_send_from_driver (transaction, connection, reply))
    goto oom;

  dbus_message_unref (reply);

  return TRUE;

 oom:
  BUS_SET_OOM (error);

 failed:
  _DBUS_ASSERT_ERROR_IS_SET (error);
  if (reply)
    dbus_message_unref (reply);
  return FALSE;
}
