gda_data_comparator_set_property (GObject *object,
				  guint param_id,
				  const GValue *value,
				  GParamSpec *pspec)
{
	GdaDataComparator *comparator;
	comparator = GDA_DATA_COMPARATOR (object);
	if (comparator->priv) {
		GdaDataModel *model;

		switch (param_id) {
		case PROP_OLD_MODEL:
			model = (GdaDataModel*) g_value_get_object (value);
			if (comparator->priv->old_model && (comparator->priv->old_model != model)) {

				clean_diff (comparator);
				g_object_unref (comparator->priv->old_model);
				g_free (comparator->priv->key_columns);
				comparator->priv->key_columns = NULL;
			}
			comparator->priv->old_model = model;
			if (model)
				g_object_ref (model);
			break;
		case PROP_NEW_MODEL:
			model = (GdaDataModel*) g_value_get_object (value);
			if (comparator->priv->new_model && (comparator->priv->new_model != model)) {

				clean_diff (comparator);
				g_object_unref (comparator->priv->new_model);
				g_free (comparator->priv->key_columns);
				comparator->priv->key_columns = NULL;
			}
			comparator->priv->new_model = model;
			if (model)
				g_object_ref (model);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
			break;
		}
	}
}
