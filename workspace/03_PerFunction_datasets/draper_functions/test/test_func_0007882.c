camel_service_ref_settings (CamelService *service)
{
	CamelSettings *settings;

	g_return_val_if_fail (CAMEL_IS_SERVICE (service), NULL);


	g_return_val_if_fail (service->priv->settings != NULL, NULL);

	g_mutex_lock (&service->priv->settings_lock);

	settings = g_object_ref (service->priv->settings);

	g_mutex_unlock (&service->priv->settings_lock);

	return settings;
}
