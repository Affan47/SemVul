camel_data_cache_new (const gchar *path,
                      GError **error)
{
	g_return_val_if_fail (path != NULL, NULL);

	if (g_mkdir_with_parents (path, 0700) == -1) {
		g_set_error (
			error, CAMEL_ERROR, CAMEL_ERROR_GENERIC,
			_("Unable to create cache path"));
		return NULL;
	}

	return g_object_new (CAMEL_TYPE_DATA_CACHE, "path", path, NULL);
}
