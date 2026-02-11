vcal_manager_load_event (const gchar *uid)
{
	GNode *node;
	gchar *path = NULL;
	VCalEvent *event = NULL;

	path = vcal_manager_get_event_file(uid);

	if (!is_file_exist(path)) {
		g_free(path);
		return NULL;
	}

	node = xml_parse_file(path);

	g_free(path);

	if (!node) {
		g_warning("no node\n");
		return NULL;
	}

	event = event_get_from_xml(uid, node);

	xml_free_tree(node);

	if (!event)
		return NULL;

	while (strchr(event->summary, '\n'))
		*(strchr(event->summary, '\n')) = ' ';

	return event;

}
