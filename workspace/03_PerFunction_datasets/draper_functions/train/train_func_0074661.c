demarshal_dhcp4_options (NMObject *object, GParamSpec *pspec, GValue *value, gpointer field)
{
	NMDHCP4ConfigPrivate *priv = NM_DHCP4_CONFIG_GET_PRIVATE (object);
	GHashTable *new_options;

	g_hash_table_remove_all (priv->options);

	new_options = g_value_get_boxed (value);
	if (new_options)
		g_hash_table_foreach (new_options, copy_options, priv->options);

	_nm_object_queue_notify (object, NM_DHCP4_CONFIG_OPTIONS);
	return TRUE;
}
