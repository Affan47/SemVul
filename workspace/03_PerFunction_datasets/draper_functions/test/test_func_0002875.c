gth_string_list_new_from_ptr_array (GPtrArray *array)
{
	GthStringList *string_list;
	int            i;

	string_list = g_object_new (GTH_TYPE_STRING_LIST, NULL);
	if (array != NULL) {
		for (i = 0; i < array->len; i++)
			string_list->priv->list = g_list_prepend (string_list->priv->list, g_strdup (g_ptr_array_index (array, i)));
		string_list->priv->list = g_list_reverse (string_list->priv->list);
	}
	else
		string_list->priv->list = NULL;

	return string_list;
}
