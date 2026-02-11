gda_data_model_array_get_row (GdaDataModelArray *model, gint row, GError **error)
{
	g_return_val_if_fail (GDA_IS_DATA_MODEL_ARRAY (model), NULL);
	g_return_val_if_fail (row >= 0, NULL);

	if ((guint)row >= model->priv->rows->len) {
		if (model->priv->rows->len > 0)
			g_set_error (error, GDA_DATA_MODEL_ERROR, GDA_DATA_MODEL_ROW_OUT_OF_RANGE_ERROR,
				     _("Row %d out of range (0-%d)"), row,
				     model->priv->rows->len - 1);
		else
			g_set_error (error, GDA_DATA_MODEL_ERROR, GDA_DATA_MODEL_ROW_OUT_OF_RANGE_ERROR,
				     _("Row %d not found (empty data model)"), row);
		return NULL;
	}

	return g_array_index (model->priv->rows, GdaRow*, row);
}
