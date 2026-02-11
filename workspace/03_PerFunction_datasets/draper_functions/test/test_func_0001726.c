__connman_plugin_init(const char *pattern, const char *exclude)
{
	gchar **patterns = NULL;
	gchar **excludes = NULL;
	GSList *list;
	GDir *dir;
	const gchar *file;
	gchar *filename;
	unsigned int i;

	DBG("");

	if (pattern)
		patterns = g_strsplit_set(pattern, ":, ", -1);

	if (exclude)
		excludes = g_strsplit_set(exclude, ":, ", -1);

	for (i = 0; __connman_builtin[i]; i++) {
		if (check_plugin(__connman_builtin[i],
						patterns, excludes) == FALSE)
			continue;

		add_plugin(NULL, __connman_builtin[i]);
	}

	dir = g_dir_open(PLUGINDIR, 0, NULL);
	if (dir != NULL) {
		while ((file = g_dir_read_name(dir)) != NULL) {
			void *handle;
			struct connman_plugin_desc *desc;

			if (g_str_has_prefix(file, "lib") == TRUE ||
					g_str_has_suffix(file, ".so") == FALSE)
				continue;

			filename = g_build_filename(PLUGINDIR, file, NULL);

			handle = dlopen(filename, PLUGINFLAG);
			if (handle == NULL) {
				connman_error("Can't load %s: %s",
							filename, dlerror());
				g_free(filename);
				continue;
			}

			g_free(filename);

			desc = dlsym(handle, "connman_plugin_desc");
			if (desc == NULL) {
				connman_error("Can't load symbol: %s",
								dlerror());
				dlclose(handle);
				continue;
			}

			if (check_plugin(desc, patterns, excludes) == FALSE) {
				dlclose(handle);
				continue;
			}

			if (add_plugin(handle, desc) == FALSE)
				dlclose(handle);
		}

		g_dir_close(dir);
	}

	for (list = plugins; list; list = list->next) {
		struct connman_plugin *plugin = list->data;

		if (plugin->desc->init() < 0)
			continue;

		plugin->active = TRUE;
	}

	g_strfreev(patterns);
	g_strfreev(excludes);

	return 0;
}
