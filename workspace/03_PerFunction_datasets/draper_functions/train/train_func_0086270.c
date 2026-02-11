gconf_settings_backend_free_notifier (GConfSettingsBackendNotifier *notifier,
                                      GConfSettingsBackend         *gconf)
{
  if (notifier->path)
    g_free (notifier->path);
  notifier->path = NULL;

  if (notifier->notify_id)
    gconf_client_notify_remove (gconf->priv->client, notifier->notify_id);
  notifier->notify_id = 0;

  g_slist_foreach (notifier->subpaths, (GFunc) gconf_settings_backend_free_notifier, gconf);
  g_slist_free (notifier->subpaths);
  notifier->subpaths = NULL;

  g_slice_free (GConfSettingsBackendNotifier, notifier);
}
