parsing_block (GcrParsed *parsed,
               gint format,
               GBytes *data)
{
	g_assert (parsed != NULL);
	g_assert (data != NULL);
	g_assert (format != 0);
	g_assert (parsed->data == NULL);

	parsed->format = format;
	parsed->data = g_bytes_ref (data);
}
