ladish_graph_find_client_by_app(ladish_graph_handle graph_handle, const uuid_t app_uuid)
{
  struct list_head * node_ptr;
  struct ladish_graph_client * client_ptr;
  uuid_t current_uuid;

  list_for_each(node_ptr, &graph_ptr->clients)
  {
    client_ptr = list_entry(node_ptr, struct ladish_graph_client, siblings);
    if(! ladish_client_get_app(client_ptr->client, current_uuid))
      continue;

    if (uuid_compare(current_uuid, app_uuid) == 0)
    {
      return client_ptr->client;
    }
  }

  return NULL;
}
