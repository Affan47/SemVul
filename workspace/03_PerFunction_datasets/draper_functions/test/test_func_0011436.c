get_authentication_agent_by_unique_system_bus_name (PolkitBackendInteractiveAuthority *authority,
                                                    const gchar *unique_system_bus_name)
{
  PolkitBackendInteractiveAuthorityPrivate *priv;
  GHashTableIter hash_iter;
  AuthenticationAgent *agent;

  priv = POLKIT_BACKEND_INTERACTIVE_AUTHORITY_GET_PRIVATE (authority);

  g_hash_table_iter_init (&hash_iter, priv->hash_scope_to_authentication_agent);
  while (g_hash_table_iter_next (&hash_iter, NULL, (gpointer) &agent))
    {
      if (strcmp (agent->unique_system_bus_name, unique_system_bus_name) == 0)
        goto out;
    }

  agent = NULL;

  out:
  return agent;
}
