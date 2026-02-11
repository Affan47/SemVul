panel_applet_container_dispose (GObject *object)
{
	PanelAppletContainer *container = PANEL_APPLET_CONTAINER (object);

	if (container->priv->pending_ops) {
		panel_applet_container_cancel_pending_operations (container);
		g_hash_table_destroy (container->priv->pending_ops);
		container->priv->pending_ops = NULL;
	}

	if (container->priv->bus_name) {
		g_free (container->priv->bus_name);
		container->priv->bus_name = NULL;
	}

	if (container->priv->name_watcher_id > 0) {
		g_bus_unwatch_name (container->priv->name_watcher_id);
		container->priv->name_watcher_id = 0;
	}

	if (container->priv->applet_proxy) {
		g_object_unref (container->priv->applet_proxy);
		container->priv->applet_proxy = NULL;
	}

	G_OBJECT_CLASS (panel_applet_container_parent_class)->dispose (object);
}
