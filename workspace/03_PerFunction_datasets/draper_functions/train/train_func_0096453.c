gda_data_access_wrapper_describe_column (GdaDataModel *model, gint col)
{
	GdaDataAccessWrapper *imodel;
	g_return_val_if_fail (GDA_IS_DATA_ACCESS_WRAPPER (model), NULL);
	imodel = (GdaDataAccessWrapper*) model;
	g_return_val_if_fail (imodel->priv, NULL);

	if (imodel->priv->model) {
		if (imodel->priv->columns)
			return g_slist_nth_data (imodel->priv->columns, col);
		else
			return gda_data_model_describe_column (imodel->priv->model, col);
	}
	else
		return NULL;
}
