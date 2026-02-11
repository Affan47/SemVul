go_plugin_service_gobject_loader_read_xml (GOPluginService *service,
					G_GNUC_UNUSED xmlNode *tree,
					G_GNUC_UNUSED GOErrorInfo **ret_error)
{
	GOPluginServiceGObjectLoaderClass *gobj_loader_class = GO_PLUGIN_SERVICE_GOBJECT_LOADER_GET_CLASS (service);
	g_return_if_fail (gobj_loader_class->pending != NULL);
	g_hash_table_replace (gobj_loader_class->pending, service->id, service);
}
