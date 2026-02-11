save_current_view (GalViewInstance *instance)
{
	xmlDoc *doc;
	xmlNode *root;

	doc = xmlNewDoc ((const guchar *)"1.0");
	root = xmlNewNode (NULL, (const guchar *)"GalViewCurrentView");
	xmlDocSetRootElement (doc, root);

	if (instance->current_id)
		e_xml_set_string_prop_by_name (root, (const guchar *)"current_view", instance->current_id);
	if (instance->current_type)
		e_xml_set_string_prop_by_name (root, (const guchar *)"current_view_type", instance->current_type);

	if (e_xml_save_file (instance->current_view_filename, doc) == -1)
		g_warning ("Unable to save view to %s - %s", instance->current_view_filename, g_strerror (errno));
	xmlFreeDoc (doc);
}
