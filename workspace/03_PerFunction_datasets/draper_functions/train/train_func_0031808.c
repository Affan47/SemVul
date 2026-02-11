gearman_client_set_log_fn(gearman_client_st *client,
                               gearman_log_fn *function, void *context,
                               gearman_verbose_t verbose)
{
  if (client)
  {
    gearman_set_log_fn(client->universal, function, context, verbose);
  }
}
