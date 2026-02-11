ladish_graph_get_connection_ports(
  ladish_graph_handle graph_handle,
  uint64_t connection_id,
  ladish_port_handle * port1_handle_ptr,
  ladish_port_handle * port2_handle_ptr)
{
  struct ladish_graph_connection * connection_ptr;

  connection_ptr = ladish_graph_find_connection_by_id(graph_ptr, connection_id);
  if (connection_ptr == NULL)
  {
    return false;
  }

  *port1_handle_ptr = connection_ptr->port1_ptr->port;
  *port2_handle_ptr = connection_ptr->port2_ptr->port;

  return true;
}
