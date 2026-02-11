database_symbol_set_file (DatabaseSymbol *object, const gchar* filename)
{
	GList *missed;
	g_assert (DATABASE_IS_SYMBOL (object));
	DatabaseSymbolPrivate *priv = DATABASE_SYMBOL_PRIVATE (object);

	if (priv->local)
	{
		g_object_unref (priv->local);
	}

	priv->local = local_symbol_new (filename);
	missed = local_symbol_get_missed_semicolons (priv->local);
	highlight_lines (missed);
}
