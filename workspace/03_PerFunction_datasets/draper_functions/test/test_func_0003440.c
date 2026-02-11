gda_data_model_array_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	GdaDataModelArray *model;

	g_return_if_fail (GDA_IS_DATA_MODEL_ARRAY (object));
	model = GDA_DATA_MODEL_ARRAY (object);

	switch (prop_id) {
	case PROP_READ_ONLY:
		model->priv->read_only = g_value_get_boolean (value);
		break;
	case PROP_N_COLUMNS:
		gda_data_model_array_set_n_columns (model, g_value_get_uint (value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
