verify (NMSetting *setting, GSList *all_settings, GError **error)
{
	NMSettingWiredPrivate *priv = NM_SETTING_WIRED_GET_PRIVATE (setting);
	const char *valid_ports[] = { "tp", "aui", "bnc", "mii", NULL };
	const char *valid_duplex[] = { "half", "full", NULL };
	const char *valid_nettype[] = { "qeth", "lcs", "ctc", NULL };
	GHashTableIter iter;
	GSList* mac_blacklist_iter;
	const char *key, *value;

	if (priv->port && !_nm_utils_string_in_list (priv->port, valid_ports)) {
		g_set_error (error,
		             NM_SETTING_WIRED_ERROR,
		             NM_SETTING_WIRED_ERROR_INVALID_PROPERTY,
		             NM_SETTING_WIRED_PORT);
		return FALSE;
	}

	if (priv->duplex && !_nm_utils_string_in_list (priv->duplex, valid_duplex)) {
		g_set_error (error,
		             NM_SETTING_WIRED_ERROR,
		             NM_SETTING_WIRED_ERROR_INVALID_PROPERTY,
		             NM_SETTING_WIRED_DUPLEX);
		return FALSE;
	}

	if (priv->device_mac_address && priv->device_mac_address->len != ETH_ALEN) {
		g_set_error (error,
		             NM_SETTING_WIRED_ERROR,
		             NM_SETTING_WIRED_ERROR_INVALID_PROPERTY,
		             NM_SETTING_WIRED_MAC_ADDRESS);
		return FALSE;
	}

	for (mac_blacklist_iter = priv->mac_address_blacklist; mac_blacklist_iter;
	     mac_blacklist_iter = mac_blacklist_iter->next) {
		struct ether_addr addr;

		if (!ether_aton_r (mac_blacklist_iter->data, &addr)) {
			g_set_error (error,
			             NM_SETTING_WIRED_ERROR,
			             NM_SETTING_WIRED_ERROR_INVALID_PROPERTY,
			             NM_SETTING_WIRED_MAC_ADDRESS_BLACKLIST);
			return FALSE;
		}
	}

	if (   priv->s390_subchannels
	    && !(priv->s390_subchannels->len == 3 || priv->s390_subchannels->len == 2)) {
		g_set_error (error,
		             NM_SETTING_WIRED_ERROR,
		             NM_SETTING_WIRED_ERROR_INVALID_PROPERTY,
		             NM_SETTING_WIRED_S390_SUBCHANNELS);
		return FALSE;
	}

	if (priv->s390_nettype && !_nm_utils_string_in_list (priv->s390_nettype, valid_nettype)) {
		g_set_error (error,
			         NM_SETTING_WIRED_ERROR,
			         NM_SETTING_WIRED_ERROR_INVALID_PROPERTY,
			         NM_SETTING_WIRED_S390_NETTYPE);
		return FALSE;
	}

	g_hash_table_iter_init (&iter, priv->s390_options);
	while (g_hash_table_iter_next (&iter, (gpointer) &key, (gpointer) &value)) {
		if (   !_nm_utils_string_in_list (key, valid_s390_opts)
		    || !strlen (value)
		    || (strlen (value) > 200)) {
			g_set_error (error,
				         NM_SETTING_WIRED_ERROR,
				         NM_SETTING_WIRED_ERROR_INVALID_PROPERTY,
				         NM_SETTING_WIRED_S390_OPTIONS);
			return FALSE;
		}
	}

	if (priv->cloned_mac_address && priv->cloned_mac_address->len != ETH_ALEN) {
		g_set_error (error,
		             NM_SETTING_WIRED_ERROR,
		             NM_SETTING_WIRED_ERROR_INVALID_PROPERTY,
		             NM_SETTING_WIRED_CLONED_MAC_ADDRESS);
		return FALSE;
	}

	return TRUE;
}
