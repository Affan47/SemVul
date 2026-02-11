pk_results_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	PkResults *results = PK_RESULTS (object);
	PkResultsPrivate *priv = results->priv;

	switch (prop_id) {
	case PROP_ROLE:
		priv->role = g_value_get_uint (value);
		break;
	case PROP_TRANSACTION_FLAGS:
		priv->transaction_flags = g_value_get_uint64 (value);
		break;
	case PROP_INPUTS:
		priv->inputs = g_value_get_uint (value);
		break;
	case PROP_PROGRESS:
		if (priv->progress != NULL)
			g_object_unref (priv->progress);
		priv->progress = g_object_ref (g_value_get_object (value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
