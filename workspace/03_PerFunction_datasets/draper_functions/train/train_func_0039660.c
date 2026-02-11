plugin_per_client_destroy (const struct plugin_common *pc, struct plugin_per_client *cli)
{
  const int n = pc->n;
  int i;

  for (i = 0; i < n; ++i)
    {
      const struct plugin *p = &pc->plugins[i];
      void *cc = cli->per_client_context[i];

      if (p->client_destructor && cc)
	(*p->client_destructor)(p->plugin_handle, cc);
    }
  CLEAR (*cli);
}
