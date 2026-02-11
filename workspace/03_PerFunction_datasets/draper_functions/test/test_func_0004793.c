__midgard_query_select_set_property (GObject *object, guint property_id,
		const GValue *value, GParamSpec *pspec)
{
	MidgardQuerySelect *self = (MidgardQuerySelect *) (object);
	GObject *mgd;
	GObject *storage;

	switch (property_id) {

		case PROPERTY_CONNECTION:
			if (!G_VALUE_HOLDS_OBJECT (value))
				return;
			MIDGARD_QUERY_EXECUTOR (self)->priv->mgd = g_value_dup_object (value);


			MidgardConfig *config = MIDGARD_QUERY_EXECUTOR (self)->priv->mgd->priv->config;
			if (config->priv->dbtype == MIDGARD_DB_TYPE_SQLITE)
				MIDGARD_QUERY_EXECUTOR (self)->priv->bool_is_int = TRUE;
			break;

		case PROPERTY_STORAGE:
			if (!G_VALUE_HOLDS_OBJECT (value))
				return;
			MIDGARD_QUERY_EXECUTOR (self)->priv->storage = g_value_dup_object (value);
			break;

  		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (self, property_id, pspec);
			break;
	}
}
