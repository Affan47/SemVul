verify (NMSetting *setting, GSList *all_settings, GError **error)
{
	NMSettingCdmaPrivate *priv = NM_SETTING_CDMA_GET_PRIVATE (setting);

	if (!priv->number) {
		g_set_error (error,
		             NM_SETTING_CDMA_ERROR,
		             NM_SETTING_CDMA_ERROR_MISSING_PROPERTY,
		             NM_SETTING_CDMA_NUMBER);
		return FALSE;
	} else if (!strlen (priv->number)) {
		g_set_error (error,
		             NM_SETTING_CDMA_ERROR,
		             NM_SETTING_CDMA_ERROR_INVALID_PROPERTY,
		             NM_SETTING_CDMA_NUMBER);
		return FALSE;
	}

	if (priv->username && !strlen (priv->username)) {
		g_set_error (error,
		             NM_SETTING_CDMA_ERROR,
		             NM_SETTING_CDMA_ERROR_INVALID_PROPERTY,
		             NM_SETTING_CDMA_USERNAME);
		return FALSE;
	}

	if (priv->password && !strlen (priv->password)) {
		g_set_error (error,
		             NM_SETTING_CDMA_ERROR,
		             NM_SETTING_CDMA_ERROR_INVALID_PROPERTY,
		             NM_SETTING_CDMA_PASSWORD);
		return FALSE;
	}

	return TRUE;
}
