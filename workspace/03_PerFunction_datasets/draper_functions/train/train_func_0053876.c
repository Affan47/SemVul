ladish_graph_find_port_by_jack_id(ladish_graph_handle graph_handle, uint64_t port_id, bool room, bool studio)
{
  struct ladish_graph_port * port_ptr;

  port_ptr = ladish_graph_find_port_by_jack_id_internal(graph_ptr, port_id, room, studio);
  if (port_ptr == NULL)
  {
    return NULL;
  }

  return port_ptr->port;
}
