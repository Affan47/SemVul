ladish_hide_connections(struct ladish_graph * graph_ptr, struct ladish_graph_port * port_ptr)
{
  struct list_head * node_ptr;
  struct ladish_graph_connection * connection_ptr;

  log_info("hidding connections of port %"PRIu64, port_ptr->id);

  ASSERT(graph_ptr->opath != NULL);

  list_for_each(node_ptr, &graph_ptr->connections)
  {
    connection_ptr = list_entry(node_ptr, struct ladish_graph_connection, siblings);
    if (!connection_ptr->hidden && (connection_ptr->port1_ptr == port_ptr || connection_ptr->port2_ptr == port_ptr))
    {
      log_info("hidding connection between ports %"PRIu64" and %"PRIu64, connection_ptr->port1_ptr->id, connection_ptr->port2_ptr->id);
      ladish_graph_hide_connection_internal(graph_ptr, connection_ptr);
    }
  }
}
