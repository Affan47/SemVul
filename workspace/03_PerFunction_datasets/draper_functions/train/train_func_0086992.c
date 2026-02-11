parse_asx_entries (TotemPlParser *parser, const char *uri, GFile *base_file, xml_node_t *parent, TotemPlParseData *parse_data)
{
	char *title = NULL;
	GFile *new_base;
	xml_node_t *node;
	TotemPlParserResult retval = TOTEM_PL_PARSER_RESULT_ERROR;

	new_base = NULL;


	for (node = parent->child; node != NULL; node = node->next) {
		if (node->name == NULL)
			continue;
		if (g_ascii_strcasecmp (node->name, "title") == 0) {
			g_free (title);
			title = g_strdup (node->data);
			totem_pl_parser_add_uri (parser,
						 TOTEM_PL_PARSER_FIELD_IS_PLAYLIST, TRUE,
						 TOTEM_PL_PARSER_FIELD_URI, uri,
						 TOTEM_PL_PARSER_FIELD_TITLE, title,
						 NULL);
		}
		if (g_ascii_strcasecmp (node->name, "base") == 0) {
			const char *str;
			str = xml_parser_get_property (node, "href");
			if (str != NULL) {
				if (new_base != NULL)
					g_object_unref (new_base);
				new_base = g_file_new_for_uri (str);
			}
		}
	}


	for (node = parent->child; node != NULL; node = node->next) {
		if (node->name == NULL)
			continue;

		if (g_ascii_strcasecmp (node->name, "entry") == 0) {

			if (parse_asx_entry (parser, new_base ? new_base : base_file, node, parse_data) != FALSE)
				retval = TOTEM_PL_PARSER_RESULT_SUCCESS;
		}
		if (g_ascii_strcasecmp (node->name, "entryref") == 0) {

			if (parse_asx_entryref (parser, new_base ? new_base : base_file, node, parse_data) != FALSE)
				retval = TOTEM_PL_PARSER_RESULT_SUCCESS;
		}
		if (g_ascii_strcasecmp (node->name, "repeat") == 0) {

			if (parse_asx_entries (parser, uri, new_base ? new_base : base_file, node, parse_data) != FALSE)
				retval = TOTEM_PL_PARSER_RESULT_SUCCESS;
		}
	}

	if (new_base != NULL)
		g_object_unref (new_base);
	if (title != NULL)
		totem_pl_parser_playlist_end (parser, uri);
	g_free (title);

	return retval;
}
