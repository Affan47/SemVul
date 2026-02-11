pk_plugin_get_data (PkPlugin *plugin, const gchar *name)
{
	const gchar *value;

	g_return_val_if_fail (PK_IS_PLUGIN (plugin), NULL);
	g_return_val_if_fail (name != NULL, NULL);

	value = g_hash_table_lookup (plugin->priv->data, name);
	g_debug ("GET: name=%s, value=%s <%p>", name, value, plugin);

	return value;
}
