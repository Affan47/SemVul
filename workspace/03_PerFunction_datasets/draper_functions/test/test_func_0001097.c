gnomeradio_xml_validate_from_resource (xmlDoc *doc, const gchar *dtd_resourcename)
{
	GBytes *resourcecontents;
	gconstpointer resourcedata;
	gsize resourcesize;
	xmlParserInputBufferPtr buffer;
	xmlValidCtxt cvp;
	xmlDtd *dtd;
	GError *error = NULL;
	gboolean ret;

	resourcecontents = g_resources_lookup_data (dtd_resourcename, G_RESOURCE_LOOKUP_FLAGS_NONE, &error);
	if (error != NULL) {
		g_warning ("Unable to load dtd resource '%s': %s", dtd_resourcename, error->message);
		g_error_free (error);
		return FALSE;
	}
	resourcedata = g_bytes_get_data (resourcecontents, &resourcesize);
	buffer = xmlParserInputBufferCreateStatic (resourcedata, resourcesize, XML_CHAR_ENCODING_UTF8);

	memset (&cvp, 0, sizeof (cvp));
	dtd = xmlIOParseDTD (NULL, buffer, XML_CHAR_ENCODING_UTF8);
	ret = xmlValidateDtd (&cvp, doc, dtd);

	xmlFreeDtd (dtd);
	g_bytes_unref (resourcecontents);

	return ret;
}
