brasero_metadata_wait (BraseroMetadata *self,
		       GCancellable *cancel)
{
	BraseroMetadataPrivate *priv;
	GCond *condition;
	gulong sig;

	priv = BRASERO_METADATA_PRIVATE (self);

	BRASERO_UTILS_LOG ("Metadata lock and wait %p", self);

	g_mutex_lock (priv->mutex);

	if (!priv->started) {


		g_mutex_unlock (priv->mutex);
		return;
	}

	condition = g_cond_new ();
	priv->conditions = g_slist_prepend (priv->conditions, condition);

	sig = g_signal_connect (cancel,
				"cancelled",
				G_CALLBACK (brasero_metadata_wait_cancelled),
				condition);

	if (!g_cancellable_is_cancelled (cancel))
		g_cond_wait (condition, priv->mutex);

	priv->conditions = g_slist_remove (priv->conditions, condition);
	g_cond_free (condition);

	g_mutex_unlock (priv->mutex);

	g_signal_handler_disconnect (cancel, sig);
}
