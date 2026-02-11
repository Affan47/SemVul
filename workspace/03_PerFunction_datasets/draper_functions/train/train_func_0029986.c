filename_from_path(const gchar *path)
{
	const gchar *base;

	if (!path) return NULL;

	base = strrchr(path, G_DIR_SEPARATOR);
	if (base) return base + 1;

	return path;
}
