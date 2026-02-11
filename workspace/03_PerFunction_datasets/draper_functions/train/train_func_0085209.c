brasero_job_set_property (GObject *object,
			  guint prop_id,
			  const GValue *value,
			  GParamSpec *pspec)
{
	BraseroJobPrivate *priv;
	BraseroTrackType *ptr;

	priv = BRASERO_JOB_PRIVATE (object);

	switch (prop_id) {
	case PROP_OUTPUT:
		ptr = g_value_get_pointer (value);
		if (!ptr) {
			priv->type.type = BRASERO_TRACK_TYPE_NONE;
			priv->type.subtype.media = BRASERO_MEDIUM_NONE;
		}
		else
			memcpy (&priv->type, ptr, sizeof (BraseroTrackType));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
