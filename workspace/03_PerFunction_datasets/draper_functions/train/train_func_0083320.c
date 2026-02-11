gigolo_settings_has_file_manager(GigoloSettings *settings)
{
	GigoloSettingsPrivate *priv;

	g_return_val_if_fail(settings != NULL, FALSE);

	priv = GIGOLO_SETTINGS_GET_PRIVATE(settings);

	return NZV(priv->file_manager);
}
