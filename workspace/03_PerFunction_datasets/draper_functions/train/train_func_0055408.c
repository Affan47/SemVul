preferences_window_dispose (GObject *object)
{
	EPreferencesWindowPrivate *priv;

	priv = E_PREFERENCES_WINDOW_GET_PRIVATE (object);

	if (priv->icon_view != NULL) {
		g_object_unref (priv->icon_view);
		priv->icon_view = NULL;
	}

	if (priv->notebook != NULL) {
		g_object_unref (priv->notebook);
		priv->notebook = NULL;
	}

	if (priv->shell) {
		g_object_remove_weak_pointer (priv->shell, &priv->shell);
		priv->shell = NULL;
	}

	g_hash_table_remove_all (priv->index);


	G_OBJECT_CLASS (e_preferences_window_parent_class)->dispose (object);
}
