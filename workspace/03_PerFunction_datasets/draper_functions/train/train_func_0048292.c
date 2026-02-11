ladish_graph_iterate_nodes(
  ladish_graph_handle graph_handle,
  void * callback_context,
  bool
  (* client_begin_callback)(
    void * context,
    ladish_graph_handle graph_handle,
    bool hidden,
    ladish_client_handle client_handle,
    const char * client_name,
    void ** client_iteration_context_ptr_ptr),
  bool
  (* port_callback)(
    void * context,
    ladish_graph_handle graph_handle,
    bool hidden,
    void * client_iteration_context_ptr,
    ladish_client_handle client_handle,
    const char * client_name,
    ladish_port_handle port_handle,
    const char * port_name,
    uint32_t port_type,
    uint32_t port_flags),
  bool
  (* client_end_callback)(
    void * context,
    ladish_graph_handle graph_handle,
    bool hidden,
    ladish_client_handle client_handle,
    const char * client_name,
    void * client_iteration_context_ptr))
{
  struct list_head * client_node_ptr;
  struct ladish_graph_client * client_ptr;
  void * client_context;
  struct list_head * port_node_ptr;
  struct list_head * port_temp_node_ptr;
  struct ladish_graph_port * port_ptr;

  list_for_each(client_node_ptr, &graph_ptr->clients)
  {
    client_ptr = list_entry(client_node_ptr, struct ladish_graph_client, siblings);

    if (client_begin_callback != NULL)
    {
      if (!client_begin_callback(callback_context, graph_handle, client_ptr->hidden, client_ptr->client, client_ptr->name, &client_context))
      {
        return false;
      }
    }
    else
    {
      client_context = NULL;
    }

    if (port_callback == NULL)
    {
      continue;
    }

    list_for_each_safe(port_node_ptr, port_temp_node_ptr, &client_ptr->ports)
    {
      port_ptr = list_entry(port_node_ptr, struct ladish_graph_port, siblings_client);

      if (!port_callback(
            callback_context,
            graph_handle,
            port_ptr->hidden,
            client_context,
            client_ptr->client,
            client_ptr->name,
            port_ptr->port,
            port_ptr->name,
            port_ptr->type,
            port_ptr->flags))
      {
        return false;
      }
    }

    if (client_end_callback != NULL)
    {
      if (!client_end_callback(callback_context, graph_handle, client_ptr->hidden, client_ptr->client, client_ptr->name, &client_context))
      {
        return false;
      }
    }
  }

  return true;
}
