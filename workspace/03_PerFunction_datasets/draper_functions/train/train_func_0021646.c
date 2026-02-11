on_port_renamed(void * graph, DBusMessage * message_ptr)
{
  dbus_uint64_t new_graph_version;
  dbus_uint64_t client_id;
  const char * client_name;
  dbus_uint64_t port_id;
  const char * old_port_name;
  const char * new_port_name;

  if (!dbus_message_get_args(
        message_ptr,
        &cdbus_g_dbus_error,
        DBUS_TYPE_UINT64, &new_graph_version,
        DBUS_TYPE_UINT64, &client_id,
        DBUS_TYPE_STRING, &client_name,
        DBUS_TYPE_UINT64, &port_id,
        DBUS_TYPE_STRING, &old_port_name,
        DBUS_TYPE_STRING, &new_port_name,
        DBUS_TYPE_INVALID))
  {
    log_error("dbus_message_get_args() failed to extract PortRenamed signal arguments (%s)", cdbus_g_dbus_error.message);
    dbus_error_free(&cdbus_g_dbus_error);
    return;
  }

  if (new_graph_version > graph_ptr->version)
  {

    graph_ptr->version = new_graph_version;
    port_renamed(graph_ptr, client_id, port_id, old_port_name, new_port_name);
  }
}
