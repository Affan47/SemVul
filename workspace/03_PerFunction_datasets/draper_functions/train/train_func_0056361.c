unity_webapps_action_manager_finalize (GObject *object)
{
  UnityWebappsActionManager *manager;

  manager = UNITY_WEBAPPS_ACTION_MANAGER (object);

  g_hash_table_destroy (manager->priv->actions_by_path);
  g_hash_table_destroy (manager->priv->infos_by_interest_id);

  if (manager->priv->menu_path)
    {
      g_free (manager->priv->menu_path);
    }
}
