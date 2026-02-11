PILListPlugins(PILPluginUniv* u, const char * pitype
,	int *		picount	)
{
	PILPluginType*	t;
	if ((t = g_hash_table_lookup(u->PluginTypes, pitype)) == NULL) {
		if (picount) {
			*picount = 0;
		}
		t = NewPILPluginType(u, pitype);
		if (!t) {
			return NULL;
		}
	}
	return PILPluginTypeListPlugins(t, picount);
}
