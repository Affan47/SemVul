gda_postgres_provider_begin_transaction (GdaServerProvider *provider, GdaConnection *cnc,
					 const gchar *name, GdaTransactionIsolation level,
					 GError **error)
{
	PostgresConnectionData *cdata;

	g_return_val_if_fail (GDA_IS_CONNECTION (cnc), FALSE);
	g_return_val_if_fail (gda_connection_get_provider (cnc) == provider, FALSE);

	cdata = (PostgresConnectionData*) gda_connection_internal_get_provider_data_error (cnc, error);
	if (!cdata)
		return FALSE;


	gchar *write_option = NULL;
        gchar *isolation_level = NULL;
	GdaStatement *stmt = NULL;

	if (cdata->reuseable->version_float >= 6.5){
                if (gda_connection_get_options (cnc) & GDA_CONNECTION_OPTIONS_READ_ONLY) {
                        if (cdata->reuseable->version_float >= 7.4)
                                write_option = "READ ONLY";
                        else {
				g_set_error (error, GDA_SERVER_PROVIDER_ERROR, GDA_SERVER_PROVIDER_NON_SUPPORTED_ERROR,
					     "%s", _("Transactions are not supported in read-only mode"));
                                gda_connection_add_event_string (cnc, _("Transactions are not supported in read-only mode"));
                                return FALSE;
                        }
                }
                switch (level) {
                case GDA_TRANSACTION_ISOLATION_READ_COMMITTED :
                        isolation_level = g_strconcat ("SET TRANSACTION ISOLATION LEVEL READ COMMITTED ", write_option, NULL);
                        break;
                case GDA_TRANSACTION_ISOLATION_READ_UNCOMMITTED:
			g_set_error (error, GDA_SERVER_PROVIDER_ERROR, GDA_SERVER_PROVIDER_NON_SUPPORTED_ERROR,
				     "%s", _("Transactions are not supported in read uncommitted isolation level"));
                        gda_connection_add_event_string (cnc,
							 _("Transactions are not supported in read uncommitted isolation level"));
                        return FALSE;
                case GDA_TRANSACTION_ISOLATION_REPEATABLE_READ:
			g_set_error (error, GDA_SERVER_PROVIDER_ERROR, GDA_SERVER_PROVIDER_NON_SUPPORTED_ERROR,
				     "%s", _("Transactions are not supported in repeatable read isolation level"));
                        gda_connection_add_event_string (cnc,
							 _("Transactions are not supported in repeatable read isolation level"));
                        return FALSE;
                case GDA_TRANSACTION_ISOLATION_SERIALIZABLE :
                        isolation_level = g_strconcat ("SET TRANSACTION ISOLATION LEVEL SERIALIZABLE ", write_option, NULL);
                        break;
                default:
                        isolation_level = NULL;
                }
        }

	if (isolation_level) {
		GdaSqlParser *parser;
		parser = gda_server_provider_internal_get_parser (provider);
		stmt = gda_sql_parser_parse_string (parser, isolation_level, NULL, NULL);
		g_free (isolation_level);
		if (!stmt) {
			g_set_error (error, GDA_SERVER_PROVIDER_ERROR, GDA_SERVER_PROVIDER_INTERNAL_ERROR,
				     "%s", _("Internal error"));
			return FALSE;
		}
	}


	if (gda_connection_statement_execute_non_select (cnc, internal_stmt [I_STMT_BEGIN], NULL, NULL, error) == -1)
		return FALSE;

	if (stmt) {
		if (gda_connection_statement_execute_non_select (cnc, stmt, NULL, NULL, error) == -1) {
			g_object_unref (stmt);
			gda_postgres_provider_rollback_transaction (provider, cnc, name, NULL);
			return FALSE;
		}
		g_object_unref (stmt);
	}

	return TRUE;
}
