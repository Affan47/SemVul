field_set_to_none (const gchar *text)
{
	const gchar *pos;
	const gchar *none_string;
	gint n;

	pos = text;
	while (n = (gint)((guchar) * pos), isspace (n))
		pos++;


	none_string = C_("date", "None");

	if (*pos == '\0' || !strncmp (pos, none_string, strlen (none_string)))
		return TRUE;
	return FALSE;
}
