parse_smil_entry (TotemPlParser *parser,
		  GFile *base_file,
		  xml_node_t *doc,
		  xml_node_t *parent,
		  const char *parent_title)
{
	xml_node_t *node;
	const char *title, *uri, *author, *abstract, *dur, *clip_begin, *copyright, *subtitle_uri;
	TotemPlParserResult retval = TOTEM_PL_PARSER_RESULT_ERROR;
	gboolean added;

	title = NULL;
	uri = NULL;
	subtitle_uri = NULL;
	author = NULL;
	abstract = NULL;
	dur = NULL;
	clip_begin = NULL;
	copyright = NULL;
	added = FALSE;

	for (node = parent->child; node != NULL; node = node->next) {
		if (node->name == NULL)
			continue;


		if (g_ascii_strcasecmp (node->name, "video") == 0
		    || g_ascii_strcasecmp (node->name, "audio") == 0
		    || g_ascii_strcasecmp (node->name, "media") == 0) {

			if (uri != NULL && added == FALSE) {
				parse_smil_entry_add (parser,
						      base_file,
						      uri,
						      title ? title : parent_title,
						      abstract,
						      copyright,
						      author,
						      clip_begin,
						      dur,
						      subtitle_uri);
				added = TRUE;
				retval = TOTEM_PL_PARSER_RESULT_SUCCESS;
			}

			uri = xml_parser_get_property (node, "src");
			title = xml_parser_get_property (node, "title");
			author = xml_parser_get_property (node, "author");
			dur = xml_parser_get_property (node, "dur");
			clip_begin = xml_parser_get_property (node, "clip-begin");
			abstract = xml_parser_get_property (node, "abstract");
			copyright = xml_parser_get_property (node, "copyright");
			subtitle_uri = NULL;
			added = FALSE;
		} else if (g_ascii_strcasecmp (node->name, "textstream") == 0) {
			subtitle_uri = xml_parser_get_property (node, "src");
		} else {
			if (parse_smil_entry (parser,
						base_file, doc, node, parent_title) != FALSE)
				retval = TOTEM_PL_PARSER_RESULT_SUCCESS;
		}
	}

	if (uri != NULL && added == FALSE) {
		parse_smil_entry_add (parser,
				      base_file,
				      uri,
				      title ? title : parent_title,
				      abstract,
				      copyright,
				      author,
				      clip_begin,
				      dur,
				      subtitle_uri);
		added = TRUE;
		retval = TOTEM_PL_PARSER_RESULT_SUCCESS;
	}

	return retval;
}
