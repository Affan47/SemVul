gda_data_model_array_get_value_at (GdaDataModel *model, gint col, gint row, GError **error)
{
	GdaRow *fields;
	GdaDataModelArray *amodel = (GdaDataModelArray*) model;

	g_return_val_if_fail(row >= 0, NULL);

	if (amodel->priv->rows->len == 0) {
		g_set_error (error, GDA_DATA_MODEL_ERROR, GDA_DATA_MODEL_ROW_NOT_FOUND_ERROR,
			      "%s", _("No row in data model"));
		return NULL;
	}

	if ((guint)row >= amodel->priv->rows->len) {
		if (amodel->priv->rows->len > 0)
			g_set_error (error, GDA_DATA_MODEL_ERROR, GDA_DATA_MODEL_ROW_OUT_OF_RANGE_ERROR,
				     _("Row %d out of range (0-%d)"), row, amodel->priv->rows->len - 1);
		else
			g_set_error (error, GDA_DATA_MODEL_ERROR, GDA_DATA_MODEL_ROW_OUT_OF_RANGE_ERROR,
				     _("Row %d not found (empty data model)"), row);
		return NULL;
	}

	if (col >= amodel->priv->number_of_columns) {
		g_set_error (error, GDA_DATA_MODEL_ERROR, GDA_DATA_MODEL_COLUMN_OUT_OF_RANGE_ERROR,
			     _("Column %d out of range (0-%d)"), col, amodel->priv->number_of_columns - 1);
		return NULL;
	}

	fields = g_array_index (amodel->priv->rows, GdaRow*, row);
	if (fields) {
		GValue *field;

		field = gda_row_get_value (fields, col);
		if (gda_row_value_is_valid (fields, field))
			return (const GValue *) field;
		else
			return NULL;
	}
	else {
		g_set_error (error, GDA_DATA_MODEL_ERROR, GDA_DATA_MODEL_ROW_NOT_FOUND_ERROR,
			      "%s", _("Data model has no data"));
		return NULL;
	}
}
