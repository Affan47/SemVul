get_cert_path (const char *keyfile_path, GByteArray *cert_path)
{
	const char *base;
	char *p = NULL, *path, *dirname, *tmp;

	g_return_val_if_fail (keyfile_path != NULL, NULL);
	g_return_val_if_fail (cert_path != NULL, NULL);

	base = path = g_malloc0 (cert_path->len + 1);
	memcpy (path, cert_path->data, cert_path->len);

	if (path[0] == '/')
		return path;

	p = strrchr (path, '/');
	if (p)
		base = p + 1;

	dirname = g_path_get_dirname (keyfile_path);
	tmp = g_build_path ("/", dirname, base, NULL);
	g_free (dirname);
	g_free (path);
	return tmp;
}
