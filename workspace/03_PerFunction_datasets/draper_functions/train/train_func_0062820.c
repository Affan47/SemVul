hex_dump (const guchar *data, gsize n_data)
{
	GString *result;
	gsize i;
	guchar j;

	g_assert (data);

	result = g_string_sized_new (n_data * 2 + 1);
	for (i = 0; i < n_data; ++i) {
		g_string_append (result, "\\x");

		j = data[i] >> 4 & 0xf;
		g_string_append_c (result, HEXC[j]);
		j = data[i] & 0xf;
		g_string_append_c (result, HEXC[j]);
	}

	return g_string_free (result, FALSE);
}
