sdb_engine_execute_unknown_sql (SymbolDBEngine *dbe, const gchar *sql)
{
	GdaStatement *stmt;
	GObject *res;
	SymbolDBEnginePriv *priv;

	priv = dbe->priv;

	SDB_LOCK(priv);
	stmt = gda_sql_parser_parse_string (priv->sql_parser, sql, NULL, NULL);

	if (stmt == NULL)
	{
		SDB_UNLOCK(priv);
		return FALSE;
	}

    if ((res = gda_connection_statement_execute (priv->db_connection,
												   (GdaStatement*)stmt,
												 	NULL,
													GDA_STATEMENT_MODEL_RANDOM_ACCESS,
													NULL, NULL)) == NULL)
	{
		g_object_unref (stmt);
		SDB_UNLOCK(priv);
		return FALSE;
	}
	else
	{
		g_object_unref (res);
		g_object_unref (stmt);
		SDB_UNLOCK(priv);
		return TRUE;
	}
}
