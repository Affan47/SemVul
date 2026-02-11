parse_atom_entry (TotemPlParser *parser, xml_node_t *parent)
{
	const char *title, *author, *uri, *filesize;
	const char *copyright, *pub_date, *description;
	xml_node_t *node;

	title = author = uri = filesize = NULL;
	copyright = pub_date = description = NULL;

	for (node = parent->child; node != NULL; node = node->next) {
		if (node->name == NULL)
			continue;

		if (g_ascii_strcasecmp (node->name, "title") == 0) {
			title = node->data;
		} else if (g_ascii_strcasecmp (node->name, "author") == 0) {

		} else if (g_ascii_strcasecmp (node->name, "link") == 0) {
			const char *rel;


			rel = xml_parser_get_property (node, "rel");
			if (g_ascii_strcasecmp (rel, "enclosure") == 0) {
				const char *href;


				href = xml_parser_get_property (node, "href");
				if (href == NULL)
					continue;
				uri = href;
				filesize = xml_parser_get_property (node, "length");
			} else if (g_ascii_strcasecmp (node->name, "license") == 0) {
				const char *href;

				href = xml_parser_get_property (node, "href");
				if (href == NULL)
					continue;

				copyright = href;
			}
		} else if (g_ascii_strcasecmp (node->name, "updated") == 0
			   || (g_ascii_strcasecmp (node->name, "modified") == 0 && pub_date == NULL)) {
			pub_date = node->data;
		} else if (g_ascii_strcasecmp (node->name, "summary") == 0
			   || (g_ascii_strcasecmp (node->name, "content") == 0 && description == NULL)) {
			const char *type;

			type = xml_parser_get_property (node, "content");
			if (type != NULL && g_ascii_strcasecmp (type, "text/plain") == 0)
				description = node->data;
		}

	}

	if (uri != NULL) {
		totem_pl_parser_add_uri (parser,
					 TOTEM_PL_PARSER_FIELD_TITLE, title,
					 TOTEM_PL_PARSER_FIELD_AUTHOR, author,
					 TOTEM_PL_PARSER_FIELD_URI, uri,
					 TOTEM_PL_PARSER_FIELD_FILESIZE, filesize,
					 TOTEM_PL_PARSER_FIELD_COPYRIGHT, copyright,
					 TOTEM_PL_PARSER_FIELD_PUB_DATE, pub_date,
					 TOTEM_PL_PARSER_FIELD_DESCRIPTION, description,
					 NULL);
	}

	return TOTEM_PL_PARSER_RESULT_SUCCESS;
}
