apt_cache_parser_next_line (AptCacheParser *parser, const gchar *line)
{
  switch (parser->state)
    {
    case APT_CACHE_PARSER_STATE_WANT_PACKAGE:
      {
	gchar *package_name;
	gboolean parsed;

	parsed = apt_cache_parser_parse_package_name (line, &package_name);
	if (parsed == FALSE)
	  {
	    break;
	  }
	if (g_str_has_prefix(package_name, "unity-webapps") == FALSE)
	  {
	    g_free (package_name);
	    break;
	  }

	g_message("Investigating webapp: %s \n", package_name);
	parser->current_webapp = webapp_info_new (package_name);
	parser->state = APT_CACHE_PARSER_STATE_WANT_METADATA;
	g_free (package_name);
	break;
      }
    case APT_CACHE_PARSER_STATE_WANT_METADATA:
      {

	gchar *key, *value;
	gboolean parsed;
	gboolean verified;

	if (g_strcmp0 (line, "\n") == 0)
	  {
	    g_warning("Found newline before all of metadata, skipping app");
	    parser->state = APT_CACHE_PARSER_STATE_WANT_PACKAGE;

	    webapp_info_free (parser->current_webapp);
	    parser->current_webapp = NULL;
	    break;
	  }

	parsed = apt_cache_parser_parse_metadata_field (line, &key, &value);
	if (parsed == FALSE)
	  {
	    g_warning ("Failed to parse metadata line (%s), skipping package", line);
	    parser->state = APT_CACHE_PARSER_STATE_WANT_PACKAGE;

	    webapp_info_free (parser->current_webapp);
	    parser->current_webapp = NULL;
	    break;
	  }
	parsed = apt_cache_parser_parse_metadata_keys (parser, key, value);
	if (parsed == FALSE)
	  {
	    g_warning ("Invalid metadata, skipping package");
	    parser->state = APT_CACHE_PARSER_STATE_WANT_PACKAGE;

	    webapp_info_free (parser->current_webapp);
	    parser->current_webapp = NULL;

	    g_free (key);
	    g_free (value);
	    break;
	  }

	verified = webapp_info_verify (parser->current_webapp);
	if (verified == TRUE)
	  {
	    parser->webapp_infos = g_list_append (parser->webapp_infos, parser->current_webapp);
	    parser->current_webapp = NULL;
	    parser->state = APT_CACHE_PARSER_STATE_WANT_PACKAGE;
	  }
	g_free (key);
	g_free (value);
	break;
      }
    case APT_CACHE_PARSER_STATE_INVALID:
      return FALSE;
    }
  return TRUE;
}
