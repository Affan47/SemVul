build_unescape_string (const gchar *escaped)
{
	gchar *unesc;
	gchar *end;

 	if (escaped == NULL)
		return NULL;

	unesc = g_new (gchar, strlen (escaped) + 1);
	end = unesc;

	for (; *escaped != '\0'; escaped++)
	{

		if (*escaped == '%')
		{
			*end++ = (g_ascii_xdigit_value (escaped[1]) << 4) | g_ascii_xdigit_value (escaped[2]);
			escaped += 2;
		}
		else
		{
			*end++ = *escaped;
		}
	}
	*end = '\0';

	return unesc;
}
