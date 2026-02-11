gda_capi_provider_init (GdaCapiProvider *capi_prv, G_GNUC_UNUSED GdaCapiProviderClass *klass)
{
	g_mutex_lock (&init_mutex);

	if (!internal_stmt) {
		InternalStatementItem i;
		GdaSqlParser *parser;

		parser = gda_server_provider_internal_get_parser ((GdaServerProvider*) capi_prv);
		internal_stmt = g_new0 (GdaStatement *, sizeof (internal_sql) / sizeof (gchar*));
		for (i = INTERNAL_STMT1; i < sizeof (internal_sql) / sizeof (gchar*); i++) {
			internal_stmt[i] = gda_sql_parser_parse_string (parser, internal_sql[i], NULL, NULL);
			if (!internal_stmt[i])
				g_error ("Could not parse internal statement: %s\n", internal_sql[i]);
		}
	}


	_gda_capi_provider_meta_init ((GdaServerProvider*) capi_prv);


	g_mutex_unlock (&init_mutex);
}
