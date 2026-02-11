gda_batch_dispose (GObject *object)
{
	GdaBatch *batch;

	g_return_if_fail (object != NULL);
	g_return_if_fail (GDA_IS_BATCH (object));

	batch = GDA_BATCH (object);
	if (batch->priv) {
		if (batch->priv->statements) {
			g_slist_foreach (batch->priv->statements, (GFunc) g_object_unref, NULL);
			g_slist_free (batch->priv->statements);
			batch->priv->statements = NULL;
		}
	}


	parent_class->dispose (object);
}
