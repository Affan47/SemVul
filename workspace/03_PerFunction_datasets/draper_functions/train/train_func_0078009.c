cc_wacom_panel_dispose (GObject *object)
{
	CcWacomPanelPrivate *priv = CC_WACOM_PANEL (object)->priv;

	if (priv->builder)
	{
		g_object_unref (priv->builder);
		priv->builder = NULL;
	}

	if (priv->manager)
	{
		g_signal_handler_disconnect (priv->manager, priv->device_added_id);
		g_signal_handler_disconnect (priv->manager, priv->device_removed_id);
		priv->manager = NULL;
	}

	if (priv->devices)
	{
		g_hash_table_destroy (priv->devices);
		priv->devices = NULL;
	}

	if (priv->pages)
	{
		g_hash_table_destroy (priv->pages);
		priv->pages = NULL;
	}

	G_OBJECT_CLASS (cc_wacom_panel_parent_class)->dispose (object);
}
