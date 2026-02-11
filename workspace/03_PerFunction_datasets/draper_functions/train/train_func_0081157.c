utils_7bit_text_to_locale(const char *text, char *locale)
{
	while (*text)
	{
		if (*text == '\\' && (guint) (text[1] - '0') <= 3 &&
			(guint) (text[2] - '0') <= 7 && (guint) (text[3] - '0') <= 7)
		{
			unsigned char c = (text[1] - '0') * 64 + (text[2] - '0') * 8 + text[3] - '0';

			if (isgraph(c))
			{
				*locale++ = c;
				text += 4;
				continue;
			}
		}

		*locale++ = *text++;
	}

	*locale = '\0';
}
