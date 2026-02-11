handle_language_element (ParserState *parser_state)
{


	xmlChar *lang_id, *lang_version;
	xmlChar *expected_version = BAD_CAST "2.0";

	g_return_if_fail (parser_state->error == NULL);

	lang_version = xmlTextReaderGetAttribute (parser_state->reader, BAD_CAST "version");

	if (lang_version == NULL ||
	    xmlStrcmp (expected_version, lang_version) != 0)
	{
		g_set_error (&parser_state->error,
			     PARSER_ERROR,
			     PARSER_ERROR_WRONG_VERSION,
			     "wrong language version '%s', expected '%s'",
			     lang_version ? (gchar*) lang_version : "(none)",
			     (gchar*) expected_version);
	}
	else
	{
		lang_id = xmlTextReaderGetAttribute (parser_state->reader, BAD_CAST "id");
		parser_state->current_lang_id = g_strdup ((gchar *) lang_id);
		g_hash_table_insert (parser_state->loaded_lang_ids, lang_id, lang_id);
	}

	xmlFree (lang_version);
}
