grl_filesystem_plugin_init (GrlRegistry *registry,
                            GrlPlugin *plugin,
                            GList *configs)
{
  GrlConfig *config;
  GList *chosen_uris = NULL;
  guint max_search_depth = GRILO_CONF_MAX_SEARCH_DEPTH_DEFAULT;
  gboolean handle_pls = FALSE;

  GRL_LOG_DOMAIN_INIT (filesystem_log_domain, "filesystem");

  GRL_DEBUG ("filesystem_plugin_init");


  bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");

  GrlFilesystemSource *source = grl_filesystem_source_new ();

  for (; configs; configs = g_list_next (configs)) {
    gchar *uri;
    config = GRL_CONFIG (configs->data);
    uri = grl_config_get_string (config, GRILO_CONF_CHOSEN_URI);
    if (uri) {
      chosen_uris = g_list_append (chosen_uris, uri);
    }
    if (grl_config_has_param (config, GRILO_CONF_MAX_SEARCH_DEPTH)) {
      max_search_depth = (guint)grl_config_get_int (config, GRILO_CONF_MAX_SEARCH_DEPTH);
    }
    if (grl_config_has_param (config, GRILO_CONF_HANDLE_PLS)) {
      handle_pls = grl_config_get_boolean (config, GRILO_CONF_HANDLE_PLS);
    }
  }
  source->priv->chosen_uris = chosen_uris;
  source->priv->max_search_depth = max_search_depth;
  source->priv->handle_pls = handle_pls;

  grl_registry_register_source (registry,
                                plugin,
                                GRL_SOURCE (source),
                                NULL);

  return TRUE;
}
