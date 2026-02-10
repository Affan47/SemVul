source_dispose (GObject *object)
{
	ESourcePrivate *priv;

	priv = E_SOURCE_GET_PRIVATE (object);

	if (priv->dbus_object != NULL) {
		EDBusObject *dbus_object;
		EDBusSource *dbus_source;

		dbus_object = E_DBUS_OBJECT (priv->dbus_object);

		dbus_source = e_dbus_object_get_source (dbus_object);
		if (dbus_source != NULL) {
			g_signal_handlers_disconnect_matched (
				dbus_source, G_SIGNAL_MATCH_DATA,
				0, 0, NULL, NULL, object);
			g_object_unref (dbus_source);
		}

		g_object_unref (priv->dbus_object);
		priv->dbus_object = NULL;
	}

	if (priv->main_context != NULL) {
		g_main_context_unref (priv->main_context);
		priv->main_context = NULL;
	}


	g_mutex_lock (&priv->changed_lock);
	if (priv->changed != NULL) {
		g_source_destroy (priv->changed);
		g_source_unref (priv->changed);
		priv->changed = NULL;
	}
	g_mutex_unlock (&priv->changed_lock);

	g_hash_table_remove_all (priv->extensions);


	G_OBJECT_CLASS (e_source_parent_class)->dispose (object);
}
