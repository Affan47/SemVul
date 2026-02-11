cache_file_remove(const gchar *path)
{
	if (path && isfile(path) && !unlink_file(path))
		{
		DEBUG_1("Failed to remove cache file %s", path);
		}
}
