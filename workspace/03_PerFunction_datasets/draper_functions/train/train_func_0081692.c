remove_pending_ready (UnityWebappsService *service, const gchar *id)
{
  GList *invocations, *walk;

  invocations = g_hash_table_lookup (service->pending_ready, id);

  for (walk = invocations; walk != NULL; walk = walk->next)
    {


    }

  g_list_free (invocations);

  g_hash_table_remove (service->pending_ready, id);
}
