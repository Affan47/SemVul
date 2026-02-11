nm_ip4_config_add_nameserver (NMIP4Config *config, guint32 nameserver)
{
	NMIP4ConfigPrivate *priv;
	int i;

	g_return_if_fail (NM_IS_IP4_CONFIG (config));
	g_return_if_fail (nameserver > 0);

	priv = NM_IP4_CONFIG_GET_PRIVATE (config);
	for (i = 0; i < priv->nameservers->len; i++) {
		guint32 s = g_array_index (priv->nameservers, guint32, i);


		if (nameserver == s)
			return;
	}

	g_array_append_val (priv->nameservers, nameserver);
}
