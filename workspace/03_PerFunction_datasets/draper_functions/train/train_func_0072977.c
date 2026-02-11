reset_array (GArray *array)
{
	gint i = 0;
	gchar *tmp = NULL;


	for (i = 0; i < array->len; i++) {
		tmp = g_array_index (array, gchar *, i);
		g_free (tmp);
	}


	g_array_set_size (array, 0);
}
