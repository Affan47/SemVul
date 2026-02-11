parse_smil_head (TotemPlParser *parser, xml_node_t *doc, xml_node_t *parent)
{
	xml_node_t *node;
	const char *title;

	title = NULL;

	for (node = parent->child; node != NULL; node = node->next) {
		if (g_ascii_strcasecmp (node->name, "meta") == 0) {
			const char *prop;
			prop = xml_parser_get_property (node, "name");
			if (prop != NULL && g_ascii_strcasecmp (prop, "title") == 0) {
				title = xml_parser_get_property (node, "content");
				if (title != NULL)
					break;
			}
		}
	}

	return title;
}
