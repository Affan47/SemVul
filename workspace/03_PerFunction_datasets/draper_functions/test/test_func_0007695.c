ladish_graph_create(ladish_graph_handle * graph_handle_ptr, const char * opath)
{
  struct ladish_graph * graph_ptr;

  graph_ptr = malloc(sizeof(struct ladish_graph));
  if (graph_ptr == NULL)
  {
    log_error("malloc() failed to allocate struct graph_implementator");
    return false;
  }

  if (opath != NULL)
  {
    graph_ptr->opath = strdup(opath);
    if (graph_ptr->opath == NULL)
    {
      log_error("strdup() failed for graph opath");
      free(graph_ptr);
      return false;
    }
  }
  else
  {
    graph_ptr->opath = NULL;
  }

  if (!ladish_dict_create(&graph_ptr->dict))
  {
    log_error("ladish_dict_create() failed for graph");
    if (graph_ptr->opath != NULL)
    {
      free(graph_ptr->opath);
    }
    free(graph_ptr);
    return false;
  }

  INIT_LIST_HEAD(&graph_ptr->clients);
  INIT_LIST_HEAD(&graph_ptr->ports);
  INIT_LIST_HEAD(&graph_ptr->connections);

  graph_ptr->graph_version = 1;
  graph_ptr->next_client_id = 1;
  graph_ptr->next_port_id = 1;
  graph_ptr->next_connection_id = 1;

  graph_ptr->context = NULL;
  graph_ptr->connect_handler = NULL;
  graph_ptr->disconnect_handler = NULL;

  graph_ptr->persist = true;

  *graph_handle_ptr = (ladish_graph_handle)graph_ptr;
  return true;
}
