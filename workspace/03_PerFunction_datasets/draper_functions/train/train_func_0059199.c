parse_data(const char *data, guint size, const char *text)
{
	GList *urls = NULL;
	if (url_check_binary(data, size))
	{
		urls = g_list_append(urls, g_strdup(text));
	} else if (!strncasecmp(data, "<?xml", 5))
	{
		g_log(LOG_DOMAIN, G_LOG_LEVEL_DEBUG, "Detected a xml file, might be xspf");

#ifdef XSPF
		urls = url_parse_xspf_file(data, size, text);
#else
#ifdef SPIFF
		urls = url_parse_spiff_file(data, size, text);
#endif
#endif
	}

	else if (!strncasecmp(data, "[playlist]", 10))
	{
		g_log(LOG_DOMAIN, G_LOG_LEVEL_DEBUG, "Detected a PLS\n");
		urls = url_parse_pls_file(data, size);
	}

	else if (!strncasecmp(data, "#EXTM3U", 7))
	{
		g_log(LOG_DOMAIN, G_LOG_LEVEL_DEBUG, "Detected a Extended M3U\n");
		urls = url_parse_extm3u_file(data, size);
	}

	else if (!strncasecmp(data, "http://", 7))
	{
		g_log(LOG_DOMAIN, G_LOG_LEVEL_DEBUG, "Might be a M3U, or generic list\n");
		urls = url_parse_extm3u_file(data, size);
	}

	else
	{
		g_log(LOG_DOMAIN, G_LOG_LEVEL_DEBUG, "Adding url: %s\n", text);
		urls = g_list_append(urls, g_strdup(text));
	}

	return urls;
}
