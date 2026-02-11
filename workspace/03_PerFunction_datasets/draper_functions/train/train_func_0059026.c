autoload_changed_cb (GSettings			*settings,
		     const gchar		*key,
		     TotemChaptersPlugin	*plugin)
{
	g_return_if_fail (G_IS_SETTINGS (settings));
	g_return_if_fail (key != NULL);
	g_return_if_fail (TOTEM_IS_CHAPTERS_PLUGIN (plugin));

	plugin->priv->autoload = g_settings_get_boolean (settings, key);
}
