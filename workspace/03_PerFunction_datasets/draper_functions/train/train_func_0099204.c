gplp_service_load (GOPluginLoader *l, GOPluginService *s, GOErrorInfo **err)
{
	if (IS_GNM_PLUGIN_SERVICE_FUNCTION_GROUP (s))
		gplp_load_service_function_group (l, s, err);
	else
		return FALSE;
	return TRUE;
}
