byte_array_to_string (const GByteArray *array)
{
	GString *cert = NULL;
	int i;

	if (array && array->len > 0)
		cert = g_string_new (NULL);

	for (i = 0; array && i < array->len; i++) {
		g_string_append_printf (cert, "%02X", array->data[i]);
	}

	return cert ? g_string_free (cert, FALSE) : NULL;
}
