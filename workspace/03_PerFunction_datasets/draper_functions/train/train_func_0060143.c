gda_vconnection_data_model_add_model (GdaVconnectionDataModel *cnc,
				      GdaDataModel *model, const gchar *table_name, GError **error)
{
	GdaVconnectionDataModelSpec *spec;
	gboolean retval;

	spec = g_new0 (GdaVconnectionDataModelSpec, 1);
	spec->data_model = model;
	spec->create_columns_func = create_columns;
	g_object_ref (model);
	retval = gda_vconnection_data_model_add (cnc, spec, (GDestroyNotify) spec_destroy_func, table_name, error);

	return retval;
}
