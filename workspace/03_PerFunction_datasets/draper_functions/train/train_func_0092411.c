PILValidateInterfaceUniv(gpointer key, gpointer ifuniv, gpointer piuniv)
{
	PILInterfaceUniv*	Ifuniv = ifuniv;
	PILPluginUniv*	Pluginuniv = piuniv;
	g_assert(IS_PILINTERFACEUNIV(Ifuniv));
	g_assert(Pluginuniv == NULL || IS_PILPLUGINUNIV(Pluginuniv));
	g_assert(piuniv == NULL || piuniv == Ifuniv->piuniv);
	g_hash_table_foreach(Ifuniv->iftypes, PILValidateInterfaceType, ifuniv);
}
