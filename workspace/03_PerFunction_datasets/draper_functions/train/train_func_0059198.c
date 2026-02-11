gkd_secret_util_parse_path (const gchar *path, gchar **collection, gchar **item)
{
	const gchar *pos;

	g_return_val_if_fail (path, FALSE);


	if (g_str_has_prefix (path, SECRET_COLLECTION_PREFIX))
		path += strlen (SECRET_COLLECTION_PREFIX);
	else if (g_str_has_prefix (path, SECRET_ALIAS_PREFIX))
		path += strlen (SECRET_ALIAS_PREFIX);
	else
		return FALSE;


	if (path[0] != '/')
		return FALSE;
	++path;


	if (path[0] == '\0')
		return FALSE;

	pos = strchr (path, '/');


	if (pos == NULL) {
		if (collection)
			*collection = decode_object_identifier (path, -1);
		if (item)
			*item = NULL;
		return TRUE;
	}


	if (pos[1] == '\0' || strchr (pos + 1, '/'))
		return FALSE;

	if (collection)
		*collection = decode_object_identifier (path, pos - path);
	if (item)
		*item = decode_object_identifier (pos + 1, -1);
	return TRUE;
}
