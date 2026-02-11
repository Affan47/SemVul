gth_user_dir_get_file_va_list (GthDir      dir_type,
			       const char *first_element,
                               va_list     var_args)
{
	const char *user_dir;
	char       *config_dir;
	GString    *path;
	const char *element;
	char       *filename;

	switch (dir_type) {
	case GTH_DIR_CONFIG:
		user_dir = g_get_user_config_dir ();
		break;
	case GTH_DIR_CACHE:
		user_dir = g_get_user_cache_dir ();
		break;
	case GTH_DIR_DATA:
		user_dir = g_get_user_data_dir ();
		break;
	}

	config_dir = g_build_path (G_DIR_SEPARATOR_S,
				   user_dir,
				   NULL);
	path = g_string_new (config_dir);

	element = first_element;
  	while (element != NULL) {
  		if (element[0] != '\0') {
  			g_string_append (path, G_DIR_SEPARATOR_S);
  			g_string_append (path, element);
  		}
		element = va_arg (var_args, const char *);
	}

	filename = path->str;

	g_string_free (path, FALSE);
	g_free (config_dir);

	return filename;
}
