ladish_graph_add_client(ladish_graph_handle graph_handle, ladish_client_handle client_handle, const char * name, bool hidden)
{
  struct ladish_graph_client * client_ptr;

  log_info("adding client '%s' (%p) to graph %s", name, client_handle, graph_ptr->opath != NULL ? graph_ptr->opath : "JACK");

  client_ptr = malloc(sizeof(struct ladish_graph_client));
  if (client_ptr == NULL)
  {
    log_error("malloc() failed for struct ladish_graph_client");
    return false;
  }

  client_ptr->name = strdup(name);
  if (client_ptr->name == NULL)
  {
    log_error("strdup() failed for graph client name");
    free(client_ptr);
    return false;
  }

  client_ptr->id = graph_ptr->next_client_id++;
  client_ptr->client = client_handle;
  client_ptr->hidden = hidden;
  graph_ptr->graph_version++;

  INIT_LIST_HEAD(&client_ptr->ports);

  list_add_tail(&client_ptr->siblings, &graph_ptr->clients);

  if (!hidden && graph_ptr->opath != NULL)
  {
    ladish_graph_emit_client_appeared(graph_ptr, client_ptr);
  }

  return true;
}
