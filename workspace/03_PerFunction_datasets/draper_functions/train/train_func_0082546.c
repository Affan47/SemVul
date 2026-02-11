eel_g_str_list_copy (GList *list)
{
	GList *node, *result;

	result = NULL;

	for (node = g_list_last (list); node != NULL; node = node->prev) {
		result = g_list_prepend (result, g_strdup (node->data));
	}
	return result;
}
