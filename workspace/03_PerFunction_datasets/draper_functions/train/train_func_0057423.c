gearman_client_clone(gearman_client_st *client,
                                        const gearman_client_st *from)
{
  if (from == NULL)
  {
    return _client_allocate(client, false);
  }

  client= _client_allocate(client, true);

  if (client == NULL)
  {
    return client;
  }

  client->options.non_blocking= from->options.non_blocking;
  client->options.unbuffered_result= from->options.unbuffered_result;
  client->options.no_new= from->options.no_new;
  client->options.free_tasks= from->options.free_tasks;
  client->options.generate_unique= from->options.generate_unique;
  client->actions= from->actions;
  client->_do_handle[0]= 0;

  gearman_universal_clone(client->universal, from->universal);

  return client;
}
