brasero_job_get_property (GObject *object,
			  guint prop_id,
			  GValue *value,
			  GParamSpec *pspec)
{
	BraseroJobPrivate *priv;
	BraseroTrackType *ptr;

	priv = BRASERO_JOB_PRIVATE (object);

	switch (prop_id) {
	case PROP_OUTPUT:
		ptr = g_value_get_pointer (value);
		memcpy (ptr, &priv->type, sizeof (BraseroTrackType));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
