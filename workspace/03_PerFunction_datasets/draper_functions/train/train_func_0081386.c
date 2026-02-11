gplp_service_unload (GOPluginLoader *l, GOPluginService *s, GOErrorInfo **err)
{
	if (IS_GNM_PLUGIN_SERVICE_FUNCTION_GROUP (s))
		;
	else
		return FALSE;
	return TRUE;
}
