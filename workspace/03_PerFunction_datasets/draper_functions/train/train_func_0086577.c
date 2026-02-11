gda_vprovider_data_model_statement_execute (GdaServerProvider *provider, GdaConnection *cnc,
					    GdaStatement *stmt, GdaSet *params,
					    GdaStatementModelUsage model_usage,
					    GType *col_types, GdaSet **last_inserted_row,
					    guint *task_id, GdaServerProviderExecCallback async_cb,
					    gpointer cb_data, GError **error)
{
	GObject *retval;
	if (async_cb) {
                g_set_error (error, GDA_SERVER_PROVIDER_ERROR, GDA_SERVER_PROVIDER_METHOD_NON_IMPLEMENTED_ERROR,
                             "%s", _("Provider does not support asynchronous statement execution"));
                return NULL;
        }

	_gda_vconnection_set_working_obj ((GdaVconnectionDataModel*) cnc, (GObject*) stmt);
	retval = GDA_SERVER_PROVIDER_CLASS (parent_class)->statement_execute (provider, cnc, stmt, params,
									      model_usage, col_types,
									      last_inserted_row, task_id,
									      async_cb, cb_data, error);

	if (retval) {
		if (! GDA_IS_DATA_MODEL (retval))
			_gda_vconnection_set_working_obj ((GdaVconnectionDataModel*) cnc, NULL);

		gchar *sql;
		sql = gda_statement_to_sql (stmt, params, NULL);
		if (sql) {
			gchar *ptr = NULL;

			if (! g_ascii_strncasecmp (sql, "DROP", 4))
				ptr = sql + 4;
			else if (! g_ascii_strncasecmp (sql, "CREATE", 6))
				ptr = sql + 6;
			if (ptr) {

				for (; *ptr && (g_ascii_isspace (*ptr) || (*ptr == '\n')); ptr++);

				if (! g_ascii_strncasecmp (ptr, "TABLE", 5)) {

					gchar delim = 0;
					gchar *table_name, *quoted;
					for (ptr = ptr+5;
					     *ptr && (g_ascii_isspace (*ptr) || (*ptr == '\n'));
					     ptr++);
					if (*ptr == '\'') {
						delim = '\'';
						ptr++;
					}
					else if (*ptr == '"') {
						delim = '"';
						ptr++;
					}
					table_name = ptr;
					if (delim)
						for (; *ptr && (*ptr != delim) ; ptr++);
					else
						for (; *ptr && g_ascii_isalnum (*ptr); ptr++);
					*ptr = 0;
					quoted = _gda_connection_compute_table_virtual_name (GDA_CONNECTION (cnc), table_name);


					g_signal_emit_by_name (cnc, "vtable-dropped", quoted);
					g_free (quoted);
				}
			}
			g_free (sql);
		}
	}
	else
		_gda_vconnection_set_working_obj ((GdaVconnectionDataModel*) cnc, NULL);
	return retval;
}
