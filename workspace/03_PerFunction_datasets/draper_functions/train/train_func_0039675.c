create_shadow_port(
  void * context,
  ladish_port_handle port_handle,
  const char * port_name,
  uint32_t port_type,
  uint32_t port_flags)
{


  if (port_is_input(port_flags))
  {
    JACKDBUS_PORT_CLEAR_INPUT(port_flags);
    JACKDBUS_PORT_SET_OUTPUT(port_flags);
  }
  else
  {
    JACKDBUS_PORT_CLEAR_OUTPUT(port_flags);
    JACKDBUS_PORT_SET_INPUT(port_flags);
  }

  if (!ladish_graph_add_port(room_ptr->owner, room_ptr->client, port_handle, port_name, port_type, port_flags, true))
  {
    log_error("ladish_graph_add_port() failed to add link port to room owner graph");
    return false;
  }

  return true;
}
