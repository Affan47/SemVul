brasero_metadata_finalize (GObject *object)
{
	BraseroMetadataPrivate *priv;
	GSList *iter;

	priv = BRASERO_METADATA_PRIVATE (object);

	brasero_metadata_destroy_pipeline (BRASERO_METADATA (object));

	if (priv->silence) {
		g_free (priv->silence);
		priv->silence = NULL;
	}

	if (priv->error) {
		g_error_free (priv->error);
		priv->error = NULL;
	}

	if (priv->watch) {
		g_source_remove (priv->watch);
		priv->watch = 0;
	}

	if (priv->info) {
		brasero_metadata_info_free (priv->info);
		priv->info = NULL;
	}

	for (iter = priv->conditions; iter; iter = iter->next) {
		GCond *condition;

		condition = iter->data;
		g_cond_broadcast (condition);
		g_cond_free (condition);
	}
	g_slist_free (priv->conditions);
	priv->conditions = NULL;

	if (priv->mutex) {
		g_mutex_free (priv->mutex);
		priv->mutex = NULL;
	}

	G_OBJECT_CLASS (brasero_metadata_parent_class)->finalize (object);
}
