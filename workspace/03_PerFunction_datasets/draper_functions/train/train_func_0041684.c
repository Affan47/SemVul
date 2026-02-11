disconnect_ports_by_name(struct cdbus_method_call * call_ptr)
{
  const char * client1_name;
  const char * port1_name;
  const char * client2_name;
  const char * port2_name;
  struct ladish_graph_port * port1;
  struct ladish_graph_port * port2;
  struct ladish_graph_connection * connection_ptr;

  if (!dbus_message_get_args(
        call_ptr->message,
        &cdbus_g_dbus_error,
        DBUS_TYPE_STRING, &client1_name,
        DBUS_TYPE_STRING, &port1_name,
        DBUS_TYPE_STRING, &client2_name,
        DBUS_TYPE_STRING, &port2_name,
        DBUS_TYPE_INVALID))
  {
    cdbus_error(call_ptr, DBUS_ERROR_INVALID_ARGS, "Invalid arguments to method \"%s\": %s", call_ptr->method_name, cdbus_g_dbus_error.message);
    dbus_error_free(&cdbus_g_dbus_error);
    return;
  }

  log_info("disconnect_ports_by_name(\"%s\", \"%s\", \"%s\", \"%s\") called.", client1_name, port1_name, client2_name, port2_name);

  if (!ladish_graph_find_connection_ports_by_name(graph_ptr, client1_name, port1_name, client2_name, port2_name, &port1, &port2))
  {
    cdbus_error(call_ptr, DBUS_ERROR_INVALID_ARGS, "Cannot disconnect unknown ports");
    return;
  }

  connection_ptr = ladish_graph_find_connection_by_ports(graph_ptr, port1, port2);
  if (connection_ptr == NULL)
  {
    cdbus_error(call_ptr, DBUS_ERROR_INVALID_ARGS, "Cannot disconnect not connected ports");
    return;
  }

  disconnect_ports(call_ptr, connection_ptr);
}
