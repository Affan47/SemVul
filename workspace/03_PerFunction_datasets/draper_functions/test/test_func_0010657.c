source_idle_changed_cb (gpointer user_data)
{
	ESource *source = E_SOURCE (user_data);


	if (!source->priv->initialized)
		return TRUE;

	g_mutex_lock (&source->priv->changed_lock);
	if (source->priv->changed != NULL) {
		g_source_unref (source->priv->changed);
		source->priv->changed = NULL;
	}
	g_mutex_unlock (&source->priv->changed_lock);

	g_signal_emit (source, signals[CHANGED], 0);

	return FALSE;
}
