gda_data_model_get_column_name (GdaDataModel *model, gint col)
{
	GdaColumn *column;
	g_return_val_if_fail (GDA_IS_DATA_MODEL (model), NULL);

	column = gda_data_model_describe_column (model, col);
	if (column)
		return gda_column_get_name (column);
	else {
		g_warning ("%s(): can't get GdaColumn object for column %d\n", __FUNCTION__, col);
		return NULL;
	}
}
