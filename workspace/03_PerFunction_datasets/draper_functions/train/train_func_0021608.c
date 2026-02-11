gearman_client_free(gearman_client_st *client)
{
  if (client)
  {

    gearman_client_task_free_all(client);

    gearman_universal_free(client->universal);

    if (client->options.allocated)
    {
      delete client;
    }
  }
}
