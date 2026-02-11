do_import_system_sources_after_abort (SymbolDBPlugin *sdb_plugin,
								  const GPtrArray *sources_array)
{
	AnjutaPlugin *plugin;
	GPtrArray* languages_array = NULL;
	GPtrArray *to_scan_array = NULL;
	IAnjutaLanguage* lang_manager;
	gint i;

	plugin = ANJUTA_PLUGIN (sdb_plugin);

	lang_manager =	anjuta_shell_get_interface (plugin->shell, IAnjutaLanguage,
										NULL);


	languages_array = g_ptr_array_new_with_free_func (g_free);
	to_scan_array = g_ptr_array_new_with_free_func (g_free);

	if (!lang_manager)
	{
		g_critical ("LanguageManager not found");
		return;
	}

	for (i=0; i < sources_array->len; i++)
	{
		const gchar *file_mime;
		const gchar *lang;
		const gchar *local_filename;
		GFile *gfile;
		GFileInfo *gfile_info;
		IAnjutaLanguageId lang_id;

		local_filename = g_ptr_array_index (sources_array, i);

		if (local_filename == NULL)
			continue;

		gfile = g_file_new_for_path (local_filename);
		if (gfile == NULL)
			continue;

		gfile_info = g_file_query_info (gfile,
										"*",
										G_FILE_QUERY_INFO_NONE,
										NULL,
										NULL);
		if (gfile_info == NULL)
		{
			g_object_unref (gfile);
			continue;
		}

		file_mime = g_file_info_get_attribute_string (gfile_info,
										  G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE);

		lang_id = ianjuta_language_get_from_mime_type (lang_manager,
													 file_mime, NULL);

		if (!lang_id)
		{
			g_object_unref (gfile);
			g_object_unref (gfile_info);
			continue;
		}

		lang = ianjuta_language_get_name (lang_manager, lang_id, NULL);


		if (g_file_test (local_filename, G_FILE_TEST_EXISTS) == FALSE)
		{
			g_object_unref (gfile);
			g_object_unref (gfile_info);
			continue;
		}

		g_ptr_array_add (languages_array, g_strdup (lang));
		g_ptr_array_add (to_scan_array, g_strdup (local_filename));
		g_object_unref (gfile);
		g_object_unref (gfile_info);
	}


#if 0
	symbol_db_system_parse_aborted_package (sdb_plugin->sdbs,
									 to_scan_array,
									 languages_array);
#endif

	g_ptr_array_unref(to_scan_array);
	g_ptr_array_unref(languages_array);
}
