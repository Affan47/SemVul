combos_items_from_data_tree (GNode *data_tree)
{
	GNode          *row, *item;
	GPtrArray      *array = g_ptr_array_new ();
	GladeModelData *data;
	gchar          *string;

	for (row = data_tree->children; row; row = row->next)
	{
		for (item = row->children; item; item = item->next)
		{
			data = item->data;
			if (G_VALUE_TYPE (&data->value) == G_TYPE_STRING)
			{
				string = g_value_dup_string (&data->value);
				g_ptr_array_add (array, string);
				break;
			}
		}
	}

	if (array->len == 0)
		return NULL;

	g_ptr_array_add (array, NULL);

	return (gchar **)g_ptr_array_free (array, FALSE);
}
