get_authentication_agent_for_subject (PolkitBackendInteractiveAuthority *authority,
                                      PolkitSubject *subject)
{
  PolkitBackendInteractiveAuthorityPrivate *priv;
  PolkitSubject *session_for_subject = NULL;
  AuthenticationAgent *agent = NULL;
  AuthenticationAgent *agent_fallback = NULL;
  gboolean fallback = FALSE;

  priv = POLKIT_BACKEND_INTERACTIVE_AUTHORITY_GET_PRIVATE (authority);

  agent = g_hash_table_lookup (priv->hash_scope_to_authentication_agent, subject);

  if (agent == NULL && POLKIT_IS_SYSTEM_BUS_NAME (subject))
    {
      PolkitSubject *process;
      process = polkit_system_bus_name_get_process_sync (POLKIT_SYSTEM_BUS_NAME (subject),
                                                         NULL,
                                                         NULL);
      if (process != NULL)
        {
          agent = g_hash_table_lookup (priv->hash_scope_to_authentication_agent, process);
          g_object_unref (process);
        }
    }

  if (agent != NULL)
    {

      if (agent->registration_options != NULL &&
          g_variant_lookup (agent->registration_options, "fallback", "b", &fallback) &&
          fallback)
        {
          agent_fallback = agent;
          agent = NULL;
        }
      else
        {

          goto out;
        }
    }


  session_for_subject = polkit_backend_session_monitor_get_session_for_subject (priv->session_monitor,
                                                                                subject,
                                                                                NULL);
  if (session_for_subject == NULL)
    goto out;

  agent = g_hash_table_lookup (priv->hash_scope_to_authentication_agent, session_for_subject);


  if (agent == NULL && agent_fallback != NULL)
    agent = agent_fallback;

 out:
  if (session_for_subject != NULL)
    g_object_unref (session_for_subject);

  return agent;
}
