giggle_plugin_set_manager (GigglePlugin        *plugin,
			   GigglePluginManager *manager)
{
	g_return_if_fail (GIGGLE_IS_PLUGIN (plugin));
	g_return_if_fail (GIGGLE_IS_PLUGIN_MANAGER (manager) || !manager);
	g_object_set (plugin, "manager", manager, NULL);
}
