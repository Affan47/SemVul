symbol_db_engine_add_new_files_async (SymbolDBEngine *dbe,
    							IAnjutaLanguage* lang_manager,
								const gchar * project_name,
    							const gchar * project_version,
							    const GPtrArray *sources_array)
{
	GPtrArray *lang_array;
	gint i;

	g_return_val_if_fail (dbe != NULL, FALSE);
	g_return_val_if_fail (lang_manager != NULL, FALSE);
	g_return_val_if_fail (sources_array != NULL, FALSE);

	lang_array = g_ptr_array_new_with_free_func (g_free);

	for (i = 0; i < sources_array->len; i++)
	{
		IAnjutaLanguageId lang_id;
		GFile *gfile;
		GFileInfo *gfile_info;
		const gchar *file_mime;
		const gchar *lang;
		const gchar *local_filename;

		local_filename = g_ptr_array_index (sources_array, i);
		gfile = g_file_new_for_path (local_filename);
		gfile_info = g_file_query_info (gfile,
										"standard::content-type",
										G_FILE_QUERY_INFO_NONE,
										NULL,
										NULL);
		if (gfile_info == NULL)
		{
			g_warning ("GFileInfo corresponding to %s was NULL", local_filename);
			g_object_unref (gfile);
			continue;
		}

		file_mime = g_file_info_get_attribute_string (gfile_info,
										  G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE);

		lang_id = ianjuta_language_get_from_mime_type (lang_manager,
													 file_mime, NULL);

		if (!lang_id)
		{
			g_warning ("Language not found for %s was NULL", local_filename);
			g_object_unref (gfile);
			g_object_unref (gfile_info);
			continue;
		}

		lang = ianjuta_language_get_name (lang_manager, lang_id, NULL);
		g_ptr_array_add (lang_array, g_strdup (lang));
		g_object_unref (gfile);
		g_object_unref (gfile_info);
	}

	gint res = symbol_db_engine_add_new_files_full_async (dbe, project_name, project_version,
	    sources_array, lang_array, TRUE);


	g_ptr_array_unref (lang_array);

	return res;
}
