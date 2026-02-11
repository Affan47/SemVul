gkm_secret_search_set_property (GObject *obj, guint prop_id, const GValue *value,
                                    GParamSpec *pspec)
{
	GkmSecretSearch *self = GKM_SECRET_SEARCH (obj);
	switch (prop_id) {
	case PROP_COLLECTION_ID:
		g_return_if_fail (!self->collection_id);
		self->collection_id = g_value_dup_string (value);
		break;
	case PROP_FIELDS:
		g_return_if_fail (!self->fields);
		self->fields = g_value_dup_boxed (value);
		g_return_if_fail (self->fields);
		break;
	case PROP_SCHEMA_NAME:
		g_return_if_fail (self->schema_name == NULL);
		self->schema_name = g_value_dup_string (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, prop_id, pspec);
		break;
	}
}
