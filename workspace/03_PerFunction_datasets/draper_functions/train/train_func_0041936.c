eog_postasa_plugin_dispose (GObject *_plugin)
{
	EogPostasaPlugin *plugin = EOG_POSTASA_PLUGIN (_plugin);

	eog_debug_message (DEBUG_PLUGINS, "EogPostasaPlugin disposing");

#ifdef HAVE_LIBGDATA_0_9
	if (plugin->priv->authorizer) {
		g_object_unref (plugin->priv->authorizer);
		plugin->priv->authorizer = NULL;
	}
#endif

	if (plugin->priv->service) {
		g_object_unref (plugin->priv->service);
		plugin->priv->service = NULL;
	}
	if (plugin->priv->login_cancellable) {
		g_object_unref (plugin->priv->login_cancellable);
		plugin->priv->login_cancellable = NULL;
	}
	if (G_IS_OBJECT (plugin->priv->uploads_store)) {

		g_object_unref (plugin->priv->uploads_store);
		plugin->priv->uploads_store = NULL;
	}

	if (plugin->priv->eog_window) {
		g_object_unref (plugin->priv->eog_window);
		plugin->priv->eog_window = NULL;
	}

	G_OBJECT_CLASS (eog_postasa_plugin_parent_class)->dispose (_plugin);
}
