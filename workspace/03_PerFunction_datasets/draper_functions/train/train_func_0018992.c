find_string_in_list_utf8case(GList *list, const gchar *string)
{
	while (list)
		{
		gchar *haystack = list->data;

		if (haystack && strcmp(haystack, string) == 0)
			return haystack;

		list = list->next;
		}

	return NULL;
}
