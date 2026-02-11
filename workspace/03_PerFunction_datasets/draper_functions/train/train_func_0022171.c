_gda_mysql_meta_constraints_tab (G_GNUC_UNUSED GdaServerProvider  *prov,
				 GdaConnection      *cnc,
				 GdaMetaStore       *store,
				 GdaMetaContext     *context,
				 GError            **error,
				 G_GNUC_UNUSED const GValue       *table_catalog,
				 const GValue       *table_schema,
				 const GValue       *table_name,
				 const GValue       *constraint_name_n)
{
	GdaDataModel *model;
	gboolean retval;
	GdaMysqlReuseable *rdata;
	rdata = GDA_MYSQL_GET_REUSEABLE_DATA (gda_connection_internal_get_provider_data_error (cnc, error));
	if (!rdata)
		return FALSE;

	if (!gda_holder_set_value (gda_set_get_holder (i_set, "schema"), table_schema, error))
		return FALSE;
	if (!gda_holder_set_value (gda_set_get_holder (i_set, "name"), table_name, error))
		return FALSE;
	if (!constraint_name_n) {
		model = gda_connection_statement_execute_select_full (cnc,
								      internal_stmt[I_STMT_TABLES_CONSTRAINTS],
								      i_set,
								      GDA_STATEMENT_MODEL_RANDOM_ACCESS,
								      _col_types_table_constraints, error);
		if (model == NULL)
			retval = FALSE;
		else {
			gda_meta_store_set_reserved_keywords_func (store,
								   _gda_mysql_reuseable_get_reserved_keywords_func
								   ((GdaProviderReuseable*) rdata));
			retval = gda_meta_store_modify (store, context->table_name, model,
							"table_schema = ##schema::string AND table_name = ##name::string",
							error,
							"schema", table_schema, "name", table_name, NULL);
			g_object_unref (G_OBJECT(model));
		}
	} else {
		if (!gda_holder_set_value (gda_set_get_holder (i_set, "name2"), constraint_name_n, error))
			return FALSE;
		model = gda_connection_statement_execute_select_full (cnc,
								      internal_stmt[I_STMT_TABLES_CONSTRAINTS_NAMED],
								      i_set,
								      GDA_STATEMENT_MODEL_RANDOM_ACCESS,
								      _col_types_table_constraints, error);
		if (model == NULL)
			retval = FALSE;
		else {
			gda_meta_store_set_reserved_keywords_func (store,
								   _gda_mysql_reuseable_get_reserved_keywords_func
								   ((GdaProviderReuseable*) rdata));
			retval = gda_meta_store_modify (store, context->table_name, model,
							"table_schema=##schema::string AND table_name=##name::string AND constraint_name=##name2::string",
							error,
							"schema", table_schema, "name", table_name, "name2", constraint_name_n, NULL);
			g_object_unref (G_OBJECT(model));
		}
	}

	return retval;
}
