FindIF(PILPluginUniv* universe, const char *iftype, const char * ifname)
{
	PILInterfaceUniv*	puniv;
	PILInterfaceType*	ptype;

	if (universe == NULL || (puniv = universe->ifuniv) == NULL
	||	(ptype=g_hash_table_lookup(puniv->iftypes, iftype))==NULL){
		return NULL;
	}
	return g_hash_table_lookup(ptype->interfaces, ifname);
}
