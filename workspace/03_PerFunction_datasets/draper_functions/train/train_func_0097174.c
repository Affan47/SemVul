hash_to_xml_string (gpointer key,
                    gpointer value,
                    gpointer user_data)
{
	CategoryInfo *cat_info = value;
	GString *string = user_data;
	gchar *category;

	g_string_append_len (string, "  <category", 11);

	if (cat_info->is_default && cat_info->clocale_name && *cat_info->clocale_name)
		category = escape_string (cat_info->clocale_name);
	else
		category = escape_string (cat_info->display_name);
	g_string_append_printf (string, " a=\"%s\"", category);
	g_free (category);

	if (cat_info->icon_file != NULL)
		g_string_append_printf (
			string, " icon=\"%s\"", cat_info->icon_file);

	g_string_append_printf (
		string, " default=\"%d\"", cat_info->is_default ? 1 : 0);

	g_string_append_printf (
		string, " searchable=\"%d\"", cat_info->is_searchable ? 1 : 0);

	g_string_append_len (string, "/>\n", 3);
}
