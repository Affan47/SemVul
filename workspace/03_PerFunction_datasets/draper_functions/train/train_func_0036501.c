geany_project_load(const gchar *path)
{
	struct GeanyPrj *ret;
	TMWorkObject *tm_obj = NULL;
	GKeyFile *config;
	gint i = 0;
	gchar *file;
	gchar *filename, *locale_filename;
	gchar *key;
	gchar *tmp;

	debug("%s path=%s\n", __FUNCTION__, path);

	if (!path)
		return NULL;

	config = g_key_file_new();
	if (!g_key_file_load_from_file(config, path, G_KEY_FILE_NONE, NULL))
	{
		g_key_file_free(config);
		return NULL;
	}


	ret = geany_project_new();
	geany_project_set_path(ret, path);

	tmp = utils_get_setting_string(config, "project", "name", GEANY_STRING_UNTITLED);
	geany_project_set_name(ret, tmp);
	g_free(tmp);

	tmp = utils_get_setting_string(config, "project", "description", "");
	geany_project_set_description(ret, tmp);
	g_free(tmp);

	tmp = utils_get_setting_string(config, "project", "base_path", "");
	geany_project_set_base_path(ret, tmp);
	g_free(tmp);

	tmp = utils_get_setting_string(config, "project", "run_cmd", "");
	geany_project_set_run_cmd(ret, tmp);
	g_free(tmp);

	geany_project_set_type_string(ret,
				      utils_get_setting_string(config, "project", "type",
							       project_type_string[0]));
	geany_project_set_regenerate(ret,
				     g_key_file_get_boolean(config, "project", "regenerate", NULL));

	if (ret->regenerate)
	{
		geany_project_regenerate_file_list(ret);
	}
	else
	{

		key = g_strdup_printf("file%d", i);
		while ((file = g_key_file_get_string(config, "files", key, NULL)))
		{
			filename = get_full_path(path, file);

			locale_filename = utils_get_locale_from_utf8(filename);
			tm_obj = tm_source_file_new(locale_filename, FALSE,
						    filetypes_detect_from_file(filename)->name);
			g_free(locale_filename);
			if (tm_obj)
			{
				g_hash_table_insert(ret->tags, filename, tm_obj);
				tm_source_file_update(tm_obj, TRUE, FALSE, TRUE);
			}
			else
				g_free(filename);
			i++;
			g_free(key);
			g_free(file);
			key = g_strdup_printf("file%d", i);
		}
		g_free(key);
	}
	g_key_file_free(config);
	return ret;
}
