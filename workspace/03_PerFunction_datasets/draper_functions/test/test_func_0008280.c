gth_comment_update_general_attributes (GthFileData *file_data)
{
	const char *value;

	value = g_file_info_get_attribute_string (file_data->info, "comment::note");
	if (value != NULL)
		set_attribute_from_string (file_data->info,
					   "general::description",
					   value,
					   NULL);

	value = g_file_info_get_attribute_string (file_data->info, "comment::caption");
	if (value != NULL)
		set_attribute_from_string (file_data->info,
					   "general::title",
					   value,
					   NULL);

	value = g_file_info_get_attribute_string (file_data->info, "comment::place");
	if (value != NULL)
		set_attribute_from_string (file_data->info,
					   "general::location",
					   value,
					   NULL);

	if (g_file_info_has_attribute (file_data->info, "comment::rating")) {
		char *v;

		v = g_strdup_printf ("%d", g_file_info_get_attribute_int32 (file_data->info, "comment::rating"));
		set_attribute_from_string (file_data->info, "general::rating", v, NULL);

		g_free (v);
	}

	if (g_file_info_has_attribute (file_data->info, "comment::categories"))
		g_file_info_set_attribute_object (file_data->info,
						  "general::tags",
						  g_file_info_get_attribute_object (file_data->info, "comment::categories"));

	if (g_file_info_has_attribute (file_data->info, "comment::time"))
		g_file_info_set_attribute_object (file_data->info,
						  "general::datetime",
						  g_file_info_get_attribute_object (file_data->info, "comment::time"));
}
