_gda_sqlite_meta__columns (G_GNUC_UNUSED GdaServerProvider *prov, GdaConnection *cnc,
			   GdaMetaStore *store, GdaMetaContext *context, GError **error)
{
	GdaDataModel *mod_model, *tmpmodel;
	gboolean retval = TRUE;
	gint i, nrows;
	SqliteConnectionData *cdata;

	cdata = (SqliteConnectionData*) gda_connection_internal_get_provider_data_error (cnc, error);
	if (!cdata)
		return FALSE;

	tmpmodel = (GdaDataModel *) gda_connection_statement_execute (cnc, internal_stmt[I_PRAGMA_DATABASE_LIST],
								      NULL, GDA_STATEMENT_MODEL_RANDOM_ACCESS, NULL, error);
	if (!tmpmodel)
		return FALSE;

	mod_model = gda_meta_store_create_modify_data_model (store, context->table_name);
	g_assert (mod_model);

	nrows = gda_data_model_get_n_rows (tmpmodel);
	for (i = 0; i < nrows; i++) {

		GdaDataModel *tables_model;
		const gchar *schema_name;
		const GValue *cvalue = gda_data_model_get_value_at (tmpmodel, 1, i, error);
		if (!cvalue) {
			retval = FALSE;
			break;
		}
		schema_name = g_value_get_string (cvalue);
		if (!strcmp (schema_name, TMP_DATABASE_NAME))
			continue;

		gchar *str;
		GType col_types[] = {G_TYPE_STRING, G_TYPE_STRING, G_TYPE_NONE};
		GdaStatement *stmt;

		str = g_strdup_printf (SELECT_TABLES_VIEWS, schema_name);
		stmt = gda_sql_parser_parse_string (internal_parser, str, NULL, NULL);
		g_free (str);
		g_assert (stmt);
		tables_model = gda_connection_statement_execute_select_full (cnc, stmt, NULL,
									     GDA_STATEMENT_MODEL_RANDOM_ACCESS,
									     col_types, error);
		g_object_unref (stmt);
		if (!tables_model) {
			retval = FALSE;
			break;
		}

		gint tnrows, ti;
		tnrows = gda_data_model_get_n_rows (tables_model);
		for (ti = 0; ti < tnrows; ti++) {

			const GValue *cv;
			cv = gda_data_model_get_value_at (tables_model, 0, ti, error);
			if (!cv) {
				retval = FALSE;
				break;
			}
			if (!fill_columns_model (cnc, cdata, mod_model, cvalue, cv, error)) {
				retval = FALSE;
				break;
			}
		}
		g_object_unref (tables_model);
		if (!retval)
			break;
	}
	g_object_unref (tmpmodel);

	if (retval) {
		gda_meta_store_set_reserved_keywords_func (store, _gda_sqlite_get_reserved_keyword_func());
		retval = gda_meta_store_modify_with_context (store, context, mod_model, error);
	}
	g_object_unref (mod_model);

	return retval;
}
