gsm_ui_to_setting (CEPageMobile *self)
{
	CEPageMobilePrivate *priv = CE_PAGE_MOBILE_GET_PRIVATE (self);
	int net_type;
	gboolean roaming_allowed;

	switch (gtk_combo_box_get_active (priv->network_type)) {
	case NET_TYPE_3G:
		net_type = NM_SETTING_GSM_NETWORK_TYPE_UMTS_HSPA;
		break;
	case NET_TYPE_2G:
		net_type = NM_SETTING_GSM_NETWORK_TYPE_GPRS_EDGE;
		break;
	case NET_TYPE_PREFER_3G:
		net_type = NM_SETTING_GSM_NETWORK_TYPE_PREFER_UMTS_HSPA;
		break;
	case NET_TYPE_PREFER_2G:
		net_type = NM_SETTING_GSM_NETWORK_TYPE_PREFER_GPRS_EDGE;
		break;
	case NET_TYPE_PREFER_4G:
		net_type = NM_SETTING_GSM_NETWORK_TYPE_PREFER_4G;
		break;
	case NET_TYPE_4G:
		net_type = NM_SETTING_GSM_NETWORK_TYPE_4G;
		break;
	case NET_TYPE_ANY:
	default:
		net_type = NM_SETTING_GSM_NETWORK_TYPE_ANY;
		break;
	}

	roaming_allowed = gtk_toggle_button_get_active (priv->roaming_allowed);

	g_object_set (priv->setting,
	              NM_SETTING_GSM_NUMBER,       nm_entry_get_text (priv->number),
	              NM_SETTING_GSM_USERNAME,     nm_entry_get_text (priv->username),
	              NM_SETTING_GSM_PASSWORD,     nm_entry_get_text (priv->password),
	              NM_SETTING_GSM_APN,          nm_entry_get_text (priv->apn),
	              NM_SETTING_GSM_NETWORK_ID,   nm_entry_get_text (priv->network_id),
	              NM_SETTING_GSM_NETWORK_TYPE, net_type,
	              NM_SETTING_GSM_PIN,          nm_entry_get_text (priv->pin),
	              NM_SETTING_GSM_HOME_ONLY,    !roaming_allowed,
	              NULL);
}
