e2_utils_get_mnemonic_char (gchar *label)
{
	gunichar c;
	gchar *uscore = g_utf8_strchr (label, -1, (gunichar)'_');
	if (uscore == NULL)
		c = (gunichar)'\0';
	else
	{
		uscore = g_utf8_next_char (uscore);
		if (*uscore == '\0')
			c = (gunichar)'\0';
		else
		{
			c = g_utf8_get_char_validated (uscore, -1);
			if (c == (gunichar)-1 || c == (gunichar)-2)
				c = (gunichar)'\0';
			else
				c = g_unichar_tolower (c);
		}
	}
	return c;
}
