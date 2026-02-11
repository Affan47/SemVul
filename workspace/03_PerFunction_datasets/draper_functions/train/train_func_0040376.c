gsd_a11y_settings_manager_stop (GsdA11ySettingsManager *manager)
{
	if (manager->priv->interface_settings) {
		g_object_unref (manager->priv->interface_settings);
		manager->priv->interface_settings = NULL;
	}
	if (manager->priv->a11y_apps_settings) {
		g_object_unref (manager->priv->a11y_apps_settings);
		manager->priv->a11y_apps_settings = NULL;
	}
        g_debug ("Stopping a11y_settings manager");
}
