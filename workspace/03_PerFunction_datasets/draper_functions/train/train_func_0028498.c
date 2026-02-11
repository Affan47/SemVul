PILValidatePluginUniv(gpointer key, gpointer piuniv, gpointer dummy)
{
	PILPluginUniv * Muniv = piuniv;

	g_assert(IS_PILPLUGINUNIV(Muniv));
	g_assert(Muniv->rootdirlist != NULL);
	g_assert(Muniv->imports != NULL);
	g_hash_table_foreach(Muniv->PluginTypes, PILValidatePluginType, piuniv);
	PILValidateInterfaceUniv(NULL, Muniv->ifuniv, piuniv);
}
