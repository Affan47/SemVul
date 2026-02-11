convert_nemo_file (char *file)
{
	GFile *dir;
	char *uri;
	gchar *contents;
	gsize length;
	xmlDocPtr xml;

	if (!g_file_get_contents (file, &contents, &length, NULL)) {
		if (!quiet) {
			g_print ("failed to load %s\n", file);
		}
		return;
	}

	uri = get_uri_from_nemo_metafile_name (file);
	if (uri == NULL) {
		g_free (contents);
		return;
	}

	dir = g_file_new_for_uri (uri);
	g_free (uri);

	xml = xmlParseMemory (contents, length);
	g_free (contents);
	if (xml == NULL) {
		return;
	}

	convert_xml_file (xml, dir);
	xmlFreeDoc (xml);
}
