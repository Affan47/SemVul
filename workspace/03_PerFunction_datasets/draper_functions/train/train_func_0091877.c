gtt_xml_read_projects (const char * filename)
{
	GList *prjs = NULL;
	xmlDocPtr doc;
	xmlNodePtr root, project_list, project;
	xmlChar *version;

	LIBXML_TEST_VERSION;
	xmlKeepBlanksDefault(0);
	doc = xmlParseFile (filename);

	if (!doc) { gtt_err_set_code (GTT_CANT_OPEN_FILE); return NULL; }
	root = xmlDocGetRootElement(doc);


	if (!root)
	{
		xmlFreeDoc(doc);
		return NULL;
	}

	version = xmlGetProp(root, (unsigned char *)"version");
	if (!root->name || strcmp ("gtt", (char *)root->name))
	{
		xmlFreeDoc(doc);
		gtt_err_set_code (GTT_NOT_A_GTT_FILE);
		return NULL;
	}

	project_list = root->xmlChildrenNode;


	if (!project_list) {
		xmlFreeDoc(doc);
		return NULL;
	}

	if (strcmp ("project-list", (char *)project_list->name)) {
		xmlFreeDoc(doc);
		gtt_err_set_code (GTT_FILE_CORRUPT); return NULL; }

	for (project=project_list->xmlChildrenNode; project; project=project->next)
	{
		GttProject *prj;
		if (project->type != XML_ELEMENT_NODE) continue;
		prj = parse_project (project);
		prjs = g_list_append (prjs, prj);
	}

	xmlFreeDoc(doc);
	return prjs;
}
