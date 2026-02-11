__import_blob_from_xml(	MidgardConnection *mgd,
					xmlDoc *doc,
					xmlNode *node)
{
	gchar *content;
	struct stat statbuf;
	const gchar *guid = (const gchar *)xmlGetProp(node, BAD_CAST "guid");

	if (!guid) {
		MIDGARD_ERRNO_SET(mgd, MGD_ERR_INTERNAL);
		g_warning("Object's guid is empty. Can not import blob file.");
		g_free((gchar *)guid);
		xmlFreeDoc(doc);
		return FALSE;
	}

	if (!midgard_is_guid((const gchar *)guid)) {
		MIDGARD_ERRNO_SET(mgd, MGD_ERR_INTERNAL);
		g_warning("'%s' is not a valid guid", guid);
		g_free((gchar *)guid);
		xmlFreeDoc(doc);
		return FALSE;
	}

	MidgardObject *object = midgard_schema_object_factory_get_object_by_guid (mgd, guid);


	if (!object) {
		g_free((gchar *)guid);
		xmlFreeDoc(doc);
		return FALSE;
	}


	gchar *blobdir = MIDGARD_DBOBJECT (object)->dbpriv->mgd->priv->config->blobdir;

	if (!blobdir || (*blobdir != '/')
			|| (stat(blobdir, &statbuf) != 0)
			|| !S_ISDIR(statbuf.st_mode)) {
		g_warning("Blobs directory is not set");
		g_free((gchar *)guid);
		xmlFreeDoc(doc);
		return FALSE;
	}

	gchar *location;
	gchar *blobpath = NULL;
	g_object_get(G_OBJECT(object), "location", &location, NULL);
	if (strlen(location) > 1) {
		blobpath = g_strconcat(blobdir, "/", location, NULL);
	}


	content = (gchar *)xmlNodeGetContent(node);

	gsize content_length = (gsize) strlen(content);
	guchar *decoded = g_base64_decode(content, &content_length);
	g_free(content);

	FILE *fp = fopen(blobpath, "w+");
	if (NULL != fp) {
		g_free(decoded);
		g_free((gchar *)guid);
		xmlFreeDoc(doc);
		return FALSE;
	}
	size_t res_length = fwrite(decoded, sizeof(char), content_length, fp);
	fclose(fp);

	g_free(decoded);
	g_free((gchar *)guid);
	xmlFreeDoc(doc);

	if (res_length < content_length) {
		return FALSE;
	}

	return TRUE;
}
