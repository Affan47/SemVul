brasero_data_project_finalize (GObject *object)
{
	BraseroDataProjectPrivate *priv;

	priv = BRASERO_DATA_PROJECT_PRIVATE (object);
	brasero_data_project_clear (BRASERO_DATA_PROJECT (object));

	if (priv->grafts) {
		g_hash_table_destroy (priv->grafts);
		priv->grafts = NULL;
	}

	if (priv->joliet) {
		g_hash_table_destroy (priv->joliet);
		priv->joliet = NULL;
	}

	if (priv->reference) {
		g_hash_table_destroy (priv->reference);
		priv->reference = NULL;
	}

	G_OBJECT_CLASS (brasero_data_project_parent_class)->finalize (object);
}
