language_manager_find_string (gpointer key, Language* language, LangData* data)
{
	if (data->found)
		return;
	if (g_list_find_custom (language->strings, data->target, (GCompareFunc) g_ascii_strcasecmp))
	{
		DEBUG_PRINT ("Found language %i: %s", language->id, language->name);
		data->result_id = language->id;
		data->found = TRUE;
	}
}
