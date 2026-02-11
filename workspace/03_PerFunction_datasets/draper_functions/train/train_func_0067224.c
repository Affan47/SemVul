grl_config_new (const gchar *plugin, const gchar *source)
{
  g_return_val_if_fail (plugin != NULL, NULL);
  GrlConfig *config = g_object_new (GRL_TYPE_CONFIG, NULL);
  if (plugin) {
    grl_config_set_string (config, GRL_CONFIG_KEY_PLUGIN, plugin);
  }
  if (source) {
    grl_config_set_source (config, source);
  }
  return config;
}
