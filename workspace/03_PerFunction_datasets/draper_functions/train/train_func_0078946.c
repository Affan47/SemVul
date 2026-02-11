attach_hub_connection (GdaVconnectionHub *hub, HubConnection *hc, GError **error)
{
	gchar *tmp;
	GdaMetaStore *store;
	GdaMetaContext context;
	GdaConnectionOptions options;

	store = gda_connection_get_meta_store (hc->cnc);
	g_assert (store);
	g_object_get ((GObject*) hc->cnc, "options", &options, NULL);
	if (! (options & GDA_CONNECTION_OPTIONS_AUTO_META_DATA)) {

		context.table_name = "_tables";
		context.size = 0;
		if (!gda_connection_update_meta_store (hc->cnc, &context, error))
			return FALSE;
	}


	if (hc->ns) {
		GdaStatement *stmt;
		tmp = g_strdup_printf ("ATTACH ':memory:' AS %s", hc->ns);
		stmt = gda_sql_parser_parse_string (internal_parser, tmp, NULL, NULL);
		g_free (tmp);
		g_assert (stmt);
		if (gda_connection_statement_execute_non_select (GDA_CONNECTION (hub), stmt, NULL, NULL, error) == -1) {
			g_object_unref (stmt);
			return FALSE;
		}
		g_object_unref (stmt);
	}


	GdaDataModel *model;
	gint i, nrows;
	model = gda_connection_get_meta_store_data (hc->cnc, GDA_CONNECTION_META_TABLES, error, 0);
	if (!model)
		return FALSE;

	nrows = gda_data_model_get_n_rows (model);
	for (i = 0; i < nrows; i++) {
		const GValue *cv = gda_data_model_get_value_at (model, 0, i, error);
		const GValue *cv1 = gda_data_model_get_value_at (model, 2, i, error);
		if (!cv || !cv1) {
			g_object_unref (model);
			return FALSE;
		}


		if (!gda_value_differ (cv, cv1))
			continue;

		if (!table_add (hc, cv, error)) {
			g_object_unref (model);
			return FALSE;
		}
	}
	g_object_unref (model);


	g_signal_connect (store, "meta-changed", G_CALLBACK (meta_changed_cb), hc);

	hub->priv->hub_connections = g_slist_append (hub->priv->hub_connections, hc);
	return TRUE;
}
