go_component_type_service_finalize (GObject * obj)
{
	GOComponentTypeService *service = GO_COMPONENT_TYPE_SERVICE (obj);
	GSList *ptr;

	for (ptr = service->mime_types; ptr != NULL; ptr = ptr->next)
	{
		g_free (ptr->data);
	}
	g_slist_free (service->mime_types);
	service->mime_types = NULL;

	(component_type_parent_klass->finalize) (obj);
}
