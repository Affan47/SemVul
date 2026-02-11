gda_sql_parser_unlock (GdaLockable *lockable)
{
	GdaSqlParser *parser = (GdaSqlParser *) lockable;
	g_return_if_fail (parser->priv);

	gda_mutex_unlock (parser->priv->mutex);
}
