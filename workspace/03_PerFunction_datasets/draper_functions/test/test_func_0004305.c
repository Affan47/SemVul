array_foreach(GArray *array, GFunc each_func, gpointer gdata)
{
	guint size = g_array_get_element_size(array);
	gchar *end = array->data + size * array->len;
	gchar *data;

	for (data = array->data; data < end; data += size)
		each_func(data, gdata);
}
