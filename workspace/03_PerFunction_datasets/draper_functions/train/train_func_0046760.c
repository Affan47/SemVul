gda_data_model_import_get_value_at (GdaDataModel *model, gint col, gint row, GError **error)
{
	GdaDataModelImport *imodel;
	g_return_val_if_fail (GDA_IS_DATA_MODEL_IMPORT (model), NULL);
	imodel = GDA_DATA_MODEL_IMPORT (model);
	g_return_val_if_fail (imodel->priv, NULL);

	if (imodel->priv->random_access_model)

		return gda_data_model_get_value_at (imodel->priv->random_access_model, col, row, error);
	else {

		g_set_error (error, GDA_DATA_MODEL_ERROR, GDA_DATA_MODEL_ACCESS_ERROR,
			      "%s", _("Data model does not support random access"));
		return NULL;
	}
}
