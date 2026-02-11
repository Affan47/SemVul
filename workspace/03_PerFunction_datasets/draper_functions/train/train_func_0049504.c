gda_data_model_import_finalize (GObject *object)
{
	GdaDataModelImport *model = (GdaDataModelImport *) object;

	g_return_if_fail (GDA_IS_DATA_MODEL_IMPORT (model));


	if (model->priv) {
		if (model->priv->errors) {
			g_slist_foreach (model->priv->errors, (GFunc) g_error_free, NULL);
			g_slist_free (model->priv->errors);
		}

		if (model->priv->cursor_values) {
			g_slist_foreach (model->priv->cursor_values, (GFunc) gda_value_free, NULL);
			g_slist_free (model->priv->cursor_values);
			model->priv->cursor_values = NULL;
		}

		g_free (model->priv);
		model->priv = NULL;
	}


	parent_class->finalize (object);
}
