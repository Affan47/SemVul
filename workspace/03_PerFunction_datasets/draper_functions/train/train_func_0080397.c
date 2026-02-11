nm_policy_get_etc_hosts (const char *contents, gsize contents_len)
{
	char **lines = NULL, **iter;
	GString *new_contents = NULL;

	if (contents_len == 0 || !strstr (contents, ADDED_TAG))
		return NULL;

	new_contents = g_string_sized_new (contents_len);


	lines = g_strsplit_set (contents, "\n\r", -1);
	for (iter = lines; iter && *iter; iter++) {
		if (!strstr (*iter, ADDED_TAG)) {
			g_string_append (new_contents, *iter);
			g_string_append_c (new_contents, '\n');
		}
	}
	g_strfreev (lines);


	if (   (new_contents->len > 2)
	    && (new_contents->str[new_contents->len - 1] == '\n'))
		g_string_truncate (new_contents, new_contents->len - 1);

	return new_contents;
}
