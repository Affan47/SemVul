gth_file_data_attribute_equal (GthFileData *file_data,
			       const char  *attribute,
			       const char  *value)
{
	char     *v;
	gboolean  result;


	if (g_strcmp0 (value, "") == 0)
		value = NULL;

	v = gth_file_data_get_attribute_as_string (file_data, attribute);
	if (g_strcmp0 (v, "") == 0) {
		g_free (v);
		v = NULL;
	}

	result = g_strcmp0 (v, value) == 0;

	g_free (v);

	return result;
}
