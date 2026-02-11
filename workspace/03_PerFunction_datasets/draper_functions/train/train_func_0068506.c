PILValidatePlugin(gpointer key, gpointer plugin, gpointer pitype)
{
	const char * Key = key;
	const PILPlugin * Plugin = plugin;

	g_assert(IS_PILPLUGIN(Plugin));

	g_assert(Key == NULL || strcmp(Key, Plugin->plugin_name) == 0);

	g_assert (Plugin->refcnt >= 0 );


	g_assert (strcmp(Key, PI_IFMANAGER) == 0 || Plugin->dlinitfun != NULL );
	g_assert (strcmp(Plugin->plugin_name, PI_IFMANAGER) == 0
	||	Plugin->dlhandle != NULL);
	g_assert(Plugin->plugintype != NULL);
	g_assert(IS_PILPLUGINTYPE(Plugin->plugintype));
	g_assert(pitype == NULL || pitype == Plugin->plugintype);
}
