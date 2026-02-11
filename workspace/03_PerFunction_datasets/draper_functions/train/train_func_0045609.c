plugin_load_and_link(const char *type_name, int n_syms,
		    const char *names[], void *ptrs[])
{
	plugin_handle_t plug = PLUGIN_INVALID_HANDLE;
	struct stat st;
	char *head=NULL, *dir_array=NULL, *so_name = NULL,
		*file_name=NULL;
	int i=0;
	plugin_err_t err = EPLUGIN_NOTFOUND;

	if (!type_name)
		return plug;
#if defined(__CYGWIN__)
	so_name = xstrdup_printf("%s.dll", type_name);
#else
	so_name = xstrdup_printf("%s.so", type_name);
#endif
	while(so_name[i]) {
		if (so_name[i] == '/')
			so_name[i] = '_';
		i++;
	}
	if (!(dir_array = slurm_get_plugin_dir())) {
		error("plugin_load_and_link: No plugin dir given");
		xfree(so_name);
		return plug;
	}

	head = dir_array;
	for (i=0; ; i++) {
		bool got_colon = 0;
		if (dir_array[i] == ':') {
			dir_array[i] = '\0';
			got_colon = 1;
		} else if (dir_array[i] != '\0')
			continue;

		file_name = xstrdup_printf("%s/%s", head, so_name);
		debug3("Trying to load plugin %s", file_name);
		if ((stat(file_name, &st) < 0) || (!S_ISREG(st.st_mode))) {
			debug4("%s: Does not exist or not a regular file.",
			       file_name);
			xfree(file_name);
			err = EPLUGIN_NOTFOUND;
		} else {
			if ((err = plugin_load_from_file(&plug, file_name))
			   == EPLUGIN_SUCCESS) {
				if (plugin_get_syms(plug, n_syms,
						    names, ptrs) >=
				       n_syms) {
					debug3("Success.");
					xfree(file_name);
					break;
				} else {
					err = EPLUGIN_MISSING_SYMBOL;
					plug = PLUGIN_INVALID_HANDLE;
				}
			} else
				plug = PLUGIN_INVALID_HANDLE;
			xfree(file_name);
		}

		if (got_colon) {
			head = dir_array + i + 1;
		} else
			break;
	}

	xfree(dir_array);
	xfree(so_name);
	errno = err;
	return plug;
}
