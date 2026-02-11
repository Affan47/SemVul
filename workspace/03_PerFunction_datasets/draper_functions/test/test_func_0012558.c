gck_string_to_chars (guchar *data, gsize max, const gchar *string)
{
	gsize len;

	g_return_val_if_fail (data, FALSE);
	g_return_val_if_fail (max, FALSE);

	if (!string) {
		memset (data, 0, max);
		return TRUE;
	}

	len = strlen (string);
	if (len > max)
		return FALSE;

	memset (data, ' ', max);
	memcpy (data, string, len);
	return TRUE;
}
