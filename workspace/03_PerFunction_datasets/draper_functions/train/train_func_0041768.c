disconnect_ports_by_connection_id(struct cdbus_method_call * call_ptr)
{
  dbus_uint64_t connection_id;
  struct ladish_graph_connection * connection_ptr;

  if (!dbus_message_get_args(call_ptr->message, &cdbus_g_dbus_error, DBUS_TYPE_UINT64, &connection_id, DBUS_TYPE_INVALID))
  {
    cdbus_error(call_ptr, DBUS_ERROR_INVALID_ARGS, "Invalid arguments to method \"%s\": %s", call_ptr->method_name, cdbus_g_dbus_error.message);
    dbus_error_free(&cdbus_g_dbus_error);
    return;
  }

  log_info("disconnect_ports_by_connection_id(%"PRIu64") called.", connection_id);

  connection_ptr = ladish_graph_find_connection_by_id(graph_ptr, connection_id);
  if (connection_ptr == NULL)
  {
    cdbus_error(call_ptr, DBUS_ERROR_INVALID_ARGS, "Cannot find connection with id %"PRIu64, connection_id);
    return;
  }

  disconnect_ports(call_ptr, connection_ptr);
}
