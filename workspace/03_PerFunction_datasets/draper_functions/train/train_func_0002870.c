pk_plugin_set_data (PkPlugin *plugin, const gchar *name, const gchar *value)
{
	g_return_val_if_fail (PK_IS_PLUGIN (plugin), FALSE);
	g_return_val_if_fail (name != NULL, FALSE);
	g_return_val_if_fail (value != NULL, FALSE);

	g_hash_table_insert (plugin->priv->data, g_strdup (name), g_strdup (value));
	g_debug ("SET: name=%s, value=%s <%p>", name, value, plugin);

	return TRUE;
}
