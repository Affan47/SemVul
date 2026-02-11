unity_webapps_application_repository_resolve_url (UnityWebappsApplicationRepository *repository, const gchar *url)
{
  GList *app, *apps, *names;

  apps = unity_webapps_application_repository_search_index (repository,
                                                            repository->priv->local_index,
                                                            url);
  if (apps == NULL)
    {
      apps = unity_webapps_application_repository_search_index (repository,
                                                                repository->priv->available_index,
                                                                url);
    }
  if (apps == NULL)
    {
      return NULL;
    }

  names = NULL;
  for (app = apps; app != NULL; app = app->next)
    {
      UnityWebappsAvailableApplication *available_app;
      const gchar * name;

      available_app = (UnityWebappsAvailableApplication *) app->data;
      name = unity_webapps_available_application_get_name (available_app);

      if (!g_hash_table_contains(repository->priv->applications_by_name, name))
        {
          g_hash_table_insert (repository->priv->applications_by_name,
                               g_strdup (name),
                               g_object_ref (available_app));
        }
      names = g_list_append(names, (gpointer) g_strdup (name));
    }
  g_list_free (apps);

  return names;
}
