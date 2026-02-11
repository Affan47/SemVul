db_anjuta_symbol_new (const gchar *file_name)
{
	IAnjutaSymbolManager *sym_man;
	DbAnjutaSymbol *self = DB_ANJUTA_SYMBOL (g_object_new (DB_TYPE_ANJUTA_SYMBOL, NULL));
	DbAnjutaSymbolPrivate *priv = DB_ANJUTA_SYMBOL_PRIVATE (self);

	IAnjutaIterable* iter;
	AnjutaPlugin *plugin = ANJUTA_PLUGIN (getPlugin ());

	if (!plugin)
		return NULL;

	sym_man = anjuta_shell_get_interface (plugin->shell, IAnjutaSymbolManager, NULL);

	priv->file = g_file_new_for_path (file_name);
	priv->self_name = g_file_get_basename (priv->file);
	if (strcmp (priv->self_name + strlen (priv->self_name) - 3, ".js") == 0)
		priv->self_name[strlen (priv->self_name) - 3] = '\0';


	priv->query_file =
		ianjuta_symbol_manager_create_query (sym_man,
		                                     IANJUTA_SYMBOL_QUERY_SEARCH_FILE,
		                                     IANJUTA_SYMBOL_QUERY_DB_PROJECT,
		                                     NULL);
	iter = ianjuta_symbol_query_search_file (priv->query_file,
	                                         "%", priv->file, NULL);
	if (iter == NULL)
	{
		DEBUG_PRINT ("Not IN DB: %s", file_name);
		g_object_unref (self);
		return NULL;
	}
	g_object_unref (iter);

	priv->query_members =
		ianjuta_symbol_manager_create_query (sym_man,
		                                     IANJUTA_SYMBOL_QUERY_SEARCH_MEMBERS,
		                                     IANJUTA_SYMBOL_QUERY_DB_PROJECT,
		                                     NULL);
	return self;
}
