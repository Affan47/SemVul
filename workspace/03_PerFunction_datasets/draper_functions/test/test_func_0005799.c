totem_pl_parser_mime_type_from_data (gconstpointer data, int len)
{
	char *mime_type;
	gboolean uncertain;

#ifdef G_OS_WIN32
	char *content_type;

	content_type = g_content_type_guess (NULL, data, len, &uncertain);
	if (uncertain == FALSE) {
		mime_type = g_content_type_get_mime_type (content_type);
		g_free (content_type);
	} else {
		mime_type = NULL;
	}
#else
	mime_type = g_content_type_guess (NULL, data, len, &uncertain);
	if (uncertain != FALSE) {
		g_free (mime_type);
		mime_type = NULL;
	}
#endif

	if (mime_type != NULL &&
	    (strcmp (mime_type, "text/plain") == 0 ||
	     strcmp (mime_type, "application/octet-stream") == 0 ||
	     strcmp (mime_type, "application/xml") == 0 ||
	     strcmp (mime_type, "text/html") == 0)) {
		PlaylistIdenCallback func;
		guint i;

		func = NULL;

		for (i = 0; i < G_N_ELEMENTS(dual_types); i++) {
			const char *res;

			if (func == dual_types[i].iden)
				continue;
			func = dual_types[i].iden;
			if (func == NULL)
				continue;
			res = func (data, len);
			if (res != NULL) {
				g_free (mime_type);
				return g_strdup (res);
			}
		}

		return NULL;
	}

	return mime_type;
}
