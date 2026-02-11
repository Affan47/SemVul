do_get (SoupServer *server, SoupMessage *msg, const char *path)
{
	char *slash;
	struct stat st;

	if (stat (path, &st) == -1) {
		if (errno == EPERM)
			soup_message_set_status (msg, SOUP_STATUS_FORBIDDEN);
		else if (errno == ENOENT)
			soup_message_set_status (msg, SOUP_STATUS_NOT_FOUND);
		else
			soup_message_set_status (msg, SOUP_STATUS_INTERNAL_SERVER_ERROR);
		return;
	}

	if (S_ISDIR (st.st_mode)) {
		GString *listing;
		char *index_path;

		slash = strrchr (path, '/');
		if (!slash || slash[1]) {
			char *redir_uri;

			redir_uri = g_strdup_printf ("%s/", soup_message_get_uri (msg)->path);
			soup_message_set_redirect (msg, SOUP_STATUS_MOVED_PERMANENTLY,
						   redir_uri);
			g_free (redir_uri);
			return;
		}

		index_path = g_strdup_printf ("%s/index.html", path);
		if (stat (index_path, &st) != -1) {
			do_get (server, msg, index_path);
			g_free (index_path);
			return;
		}
		g_free (index_path);

		listing = get_directory_listing (path);
		soup_message_set_response (msg, "text/html",
					   SOUP_MEMORY_TAKE,
					   listing->str, listing->len);
		g_string_free (listing, FALSE);
		return;
	}

	if (msg->method == SOUP_METHOD_GET) {
		GMappedFile *mapping;
		SoupBuffer *buffer;

		mapping = g_mapped_file_new (path, FALSE, NULL);
		if (!mapping) {
			soup_message_set_status (msg, SOUP_STATUS_INTERNAL_SERVER_ERROR);
			return;
		}

		buffer = soup_buffer_new_with_owner (g_mapped_file_get_contents (mapping),
						     g_mapped_file_get_length (mapping),
						     mapping, (GDestroyNotify)g_mapped_file_unref);
		soup_message_body_append_buffer (msg->response_body, buffer);
		soup_buffer_free (buffer);
	} else  {
		char *length;


		length = g_strdup_printf ("%lu", (gulong)st.st_size);
		soup_message_headers_append (msg->response_headers,
					     "Content-Length", length);
		g_free (length);
	}

	soup_message_set_status (msg, SOUP_STATUS_OK);
}
