nm_setting_ip4_config_remove_dns_search (NMSettingIP4Config *setting, guint32 i)
{
	NMSettingIP4ConfigPrivate *priv;
	GSList *elt;

	g_return_if_fail (NM_IS_SETTING_IP4_CONFIG (setting));

	priv = NM_SETTING_IP4_CONFIG_GET_PRIVATE (setting);
	elt = g_slist_nth (priv->dns_search, i);
	g_return_if_fail (elt != NULL);

	g_free (elt->data);
	priv->dns_search = g_slist_delete_link (priv->dns_search, elt);
}
