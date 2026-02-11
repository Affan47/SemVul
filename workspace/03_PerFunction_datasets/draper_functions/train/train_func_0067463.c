get_last_char (gchar *string)
{
	size_t pos;

	g_return_val_if_fail (string != NULL, '\0');
	pos = strlen (string);
	g_return_val_if_fail (pos > 0, '\0');

	return string[pos - 1];
}
