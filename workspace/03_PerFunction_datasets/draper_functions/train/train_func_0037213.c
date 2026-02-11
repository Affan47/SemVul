polkit_agent_register_listener (PolkitAgentListener  *listener,
                                PolkitSubject        *subject,
                                const gchar          *object_path,
                                GError              **error)
{
  Server *server;
  gboolean ret;

  ret = FALSE;

  server = polkit_agent_listener_register (listener, POLKIT_AGENT_REGISTER_FLAGS_NONE, subject, object_path, NULL, error);
  if (server == NULL)
    goto out;


  g_object_unref (server->listener);

  g_object_weak_ref (G_OBJECT (server->listener), listener_died, server);

  ret = TRUE;

 out:
  return ret;
}
