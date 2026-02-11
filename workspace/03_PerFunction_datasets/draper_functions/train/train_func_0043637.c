_gda_postgres_meta_udt_cols (G_GNUC_UNUSED GdaServerProvider *prov, GdaConnection *cnc,
			     GdaMetaStore *store, GdaMetaContext *context, GError **error,
			     const GValue *udt_catalog, const GValue *udt_schema, const GValue *udt_name)
{
	GdaDataModel *model;
	gboolean retval = TRUE;
	GdaPostgresReuseable *rdata;

	rdata = GDA_POSTGRES_GET_REUSEABLE_DATA (gda_connection_internal_get_provider_data_error (cnc, error));
	if (!rdata)
		return FALSE;

	if (!gda_holder_set_value (gda_set_get_holder (i_set, "cat"), udt_catalog, error))
		return FALSE;
	if (! gda_holder_set_value (gda_set_get_holder (i_set, "schema"), udt_schema, error))
		return FALSE;
	if (! gda_holder_set_value (gda_set_get_holder (i_set, "name"), udt_name, error))
		return FALSE;
	model = gda_connection_statement_execute_select_full (cnc,
							      internal_stmt[I_STMT_UDT_COLUMNS],
							      i_set,
							      GDA_STATEMENT_MODEL_RANDOM_ACCESS,
							      _col_types_udt_columns, error);
	if (!model)
		return FALSE;

	gda_meta_store_set_reserved_keywords_func (store, _gda_postgres_reuseable_get_reserved_keywords_func
						   ((GdaProviderReuseable*) rdata));
	retval = gda_meta_store_modify_with_context (store, context, model, error);
	g_object_unref (model);

	return retval;
}
