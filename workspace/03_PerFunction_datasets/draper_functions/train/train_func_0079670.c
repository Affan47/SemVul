path_get_body (const gchar *path)
{
	gchar *beg, *end;

	g_return_val_if_fail (path, NULL);

	beg = strstr (path, "://");

	if (!beg) {
		return g_strndup (path, strcspn (path, "/"));
	}

	beg += 3;
	end = strchr (beg, '/');

	if (!end) {
		return g_strdup (path);
	}

	return g_strndup (path, end - path);
}
