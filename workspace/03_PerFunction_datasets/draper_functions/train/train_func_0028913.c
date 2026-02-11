on_client_disappeared(void * graph, DBusMessage * message_ptr)
{
  dbus_uint64_t new_graph_version;
  dbus_uint64_t client_id;
  const char * client_name;

  if (!dbus_message_get_args(
        message_ptr,
        &cdbus_g_dbus_error,
        DBUS_TYPE_UINT64, &new_graph_version,
        DBUS_TYPE_UINT64, &client_id,
        DBUS_TYPE_STRING, &client_name,
        DBUS_TYPE_INVALID))
  {
    log_error("dbus_message_get_args() failed to extract ClientDisappeared signal arguments (%s)", cdbus_g_dbus_error.message);
    dbus_error_free(&cdbus_g_dbus_error);
    return;
  }


  if (new_graph_version > graph_ptr->version)
  {

    graph_ptr->version = new_graph_version;
    client_disappeared(graph_ptr, client_id);
  }
}
