telepathy_presence_manager_get_presence (UnityWebappsPresenceManager *presence_manager,
					     gchar **status,
					     gchar **message)
{
  UnityWebappsTelepathyPresenceManager *manager;

  manager = UNITY_WEBAPPS_TELEPATHY_PRESENCE_MANAGER (presence_manager);

  if (manager->priv->account_manager == NULL)
    {
      *status = NULL;
      *message = NULL;

      return FALSE;
    }

  tp_account_manager_get_most_available_presence (manager->priv->account_manager,
						  status, message);

  if (*status == NULL)
    {
      *status = g_strdup ("available");
    }

  return TRUE;
}
