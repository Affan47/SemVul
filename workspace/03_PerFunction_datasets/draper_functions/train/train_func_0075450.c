word_count(gchar *text, guint *chars, guint *lines, guint *words)
{
	guint in_word = 0;
	gunichar utext;

	if (! text)
		return;

	*chars = *words = *lines = 0;
	while (*text != '\0')
	{
		(*chars)++;

		switch (*text)
		{
			case '\n':
				(*lines)++;
			case '\r':
			case '\f':
			case '\t':
			case ' ':
			case '\v':
				mb_word_separator:
				if (in_word)
				{
					in_word = 0;
					(*words)++;
				}
				break;
			default:
				utext = g_utf8_get_char_validated(text, 2);
				if (g_unichar_isspace(utext))
					goto mb_word_separator;
				if (g_unichar_isgraph(utext))
					in_word = 1;
				break;
		}

		text = g_utf8_next_char(text);
	}


	if (in_word)
		(*words)++;

	if (*chars > 0)
		(*lines)++;
}
