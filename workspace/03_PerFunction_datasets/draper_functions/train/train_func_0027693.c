got_vino_proxy (GObject                 *source_object,
		GAsyncResult            *res,
		GsdRemoteDisplayManager *manager)
{
	GError *error = NULL;
	GVariant *v;

	manager->priv->vino_proxy = g_dbus_proxy_new_finish (res, &error);
	if (manager->priv->vino_proxy == NULL) {
		g_warning ("Failed to get Vino's D-Bus proxy: %s", error->message);
		g_error_free (error);
		return;
	}

	g_signal_connect (manager->priv->vino_proxy, "g-properties-changed",
			  G_CALLBACK (props_changed), manager);

	v = g_dbus_proxy_get_cached_property (manager->priv->vino_proxy, "Connected");
	if (v) {
                g_debug ("Setting original state");
		update_settings_from_variant (manager, v);
                g_variant_unref (v);
        }
}
