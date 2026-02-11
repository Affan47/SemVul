plugin_manager_dispose (GObject *object)
{
	GigglePluginManagerPriv *priv = GET_PRIV (object);

	if (priv->cancellable) {
		g_cancellable_cancel (priv->cancellable);
		g_object_unref (priv->cancellable);
		priv->cancellable = NULL;
	}

	if (priv->widgets) {
		g_hash_table_destroy (priv->widgets);
		priv->widgets = NULL;
	}

	if (priv->plugin_dir) {
		g_object_unref (priv->plugin_dir);
		priv->plugin_dir = NULL;
	}

	G_OBJECT_CLASS (giggle_plugin_manager_parent_class)->dispose (object);
}
