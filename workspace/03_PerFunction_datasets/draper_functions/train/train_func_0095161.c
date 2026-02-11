file_model_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	g_return_if_fail (FILE_IS_MODEL (object));
	FileModel* model = FILE_MODEL(object);
	FileModelPrivate* priv = FILE_MODEL_GET_PRIVATE(model);

	switch (prop_id)
	{
	case PROP_BASE_PATH:
		g_value_set_object (value, priv->base_path);
		break;
	case PROP_FILTER_BINARY:
		g_value_set_boolean (value, priv->filter_binary);
	case PROP_FILTER_HIDDEN:
		g_value_set_boolean (value, priv->filter_hidden);
	case PROP_FILTER_BACKUP:
		g_value_set_boolean (value, priv->filter_backup);
	case PROP_FILTER_UNVERSIONED:
		g_value_set_boolean (value, priv->filter_unversioned);

	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
