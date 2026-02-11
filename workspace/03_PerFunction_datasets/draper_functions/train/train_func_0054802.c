get_ntp_service (GstTimeTool *tool)
{
	GObject *service;
	OobsList *list;
	OobsListIter iter;
	gboolean valid;
	GstServiceRole role;

	list = oobs_services_config_get_services (OOBS_SERVICES_CONFIG (tool->services_config));
	valid = oobs_list_get_iter_first (list, &iter);

	while (valid) {
		service = oobs_list_get (list, &iter);
		role = gst_service_get_role (OOBS_SERVICE (service));

		if (role == GST_ROLE_NTP_SERVER)
			tool->ntp_service = g_object_ref (service);

		g_object_unref (service);
		valid = oobs_list_iter_next (list, &iter);
	}
}
