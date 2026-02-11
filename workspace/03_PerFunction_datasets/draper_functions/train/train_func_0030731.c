grl_plugin_set_optional_info (GrlPlugin *plugin,
                              GHashTable *info)
{
  g_return_if_fail (GRL_IS_PLUGIN (plugin));

  g_hash_table_unref (plugin->priv->optional_info);
  plugin->priv->optional_info = info;
}
