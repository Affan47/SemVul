slapd_print_pluginlist_versions(struct slapdplugin *plg)
{
	struct slapdplugin *p,*prev = NULL;

	for (p = plg; p != NULL; p = p->plg_next) {
	  slapd_print_plugin_version(p,prev);
	  prev = p;
	}
}
