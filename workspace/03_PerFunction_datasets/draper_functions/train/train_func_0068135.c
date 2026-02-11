unity_webapps_application_repository_search_index (UnityWebappsApplicationRepository *repository, UnityWebappsUrlIndex *index, const gchar *url)
{
  GList *available_apps, *apps, *cur_available_app;

  available_apps = unity_webapps_url_index_lookup_url (index, url);

  if (available_apps == NULL)
    {
      return NULL;
    }

  apps = NULL;
  for (cur_available_app = available_apps;
       cur_available_app != NULL;
       cur_available_app = cur_available_app->next)
    {
      apps = g_list_append(apps, UNITY_WEBAPPS_AVAILABLE_APPLICATION (cur_available_app->data));
    }
  g_list_free (available_apps);

  return apps;
}
