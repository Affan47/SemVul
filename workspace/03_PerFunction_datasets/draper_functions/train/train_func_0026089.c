ladish_graph_remove_port_internal(
  struct ladish_graph * graph_ptr,
  struct ladish_graph_client * client_ptr,
  struct ladish_graph_port * port_ptr)
{
  ladish_graph_remove_port_connections(graph_ptr, port_ptr);

  ladish_port_del_ref(port_ptr->port);

  list_del(&port_ptr->siblings_client);
  list_del(&port_ptr->siblings_graph);

  log_info("removing port '%s':'%s' (%"PRIu64":%"PRIu64") from graph %s", client_ptr->name, port_ptr->name, client_ptr->id, port_ptr->id, graph_ptr->opath != NULL ? graph_ptr->opath : "JACK");
  if (graph_ptr->opath != NULL && !port_ptr->hidden)
  {
    ASSERT(port_ptr->client_ptr == client_ptr);
    ladish_graph_emit_port_disappeared(graph_ptr, port_ptr);
  }

  free(port_ptr->name);
  free(port_ptr);
}
