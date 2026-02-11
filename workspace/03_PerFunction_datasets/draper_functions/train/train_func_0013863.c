is_empty_line (const gchar *text)
{
	if (*text != '\0')
	{
		const gchar *p;

		for (p = text; p != NULL; p = g_utf8_next_char (p))
		{
			if (!g_unichar_isspace (*p))
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}
