print_markup(const char *str, int len)
{
	int l;
	char c;
	const char *p;
	bool comma;
	bool quote;

	if (len <= 0)
		return;


	p = str;
	while (len > 0)
	{
		c = *str++;
		len--;
		if (c == ' ')
			break;
	}

	l = str - p - (c == ' ');
	if (l <= 0)
		THROW(E_SYNTAX);

	FORM_print_len(p, l);
	FORM_print("._Render(");

	if (len > 0)
	{
		FORM_print_char('[');

		comma = FALSE;

		while (len > 0)
		{
			while (len > 0 && *str == ' ')
			{
				str++;
				len--;
			}

			p = str;
			while (len > 0)
			{
				c = *str++;
				len--;
				if (c == '=' || c == ' ')
					break;
			}

			if (comma)
				FORM_print(", ");

			FORM_print_char('"');
			l = str - p - (c == '=');
			print_lower_len(p, l);
			FORM_print("\": ");

			comma = TRUE;

			if (len <= 0 || c == ' ')
			{
				FORM_print("True");
				continue;
			}

			p = str;

			if (*str == '"')
			{
				str++;
				len--;
				quote = TRUE;
			}
			else
			{
				quote = FALSE;
			}

			while (len > 0)
			{
				c = *str++;
				len--;
				if ((quote && c == '"') || (!quote && c == ' '))
					break;
			}

			if (!quote && str == p)
				FORM_print("True");
			else
			{
				if (!quote)
					FORM_print_char('"');
				FORM_print_len(p, str - p);
				if (!quote)
					FORM_print_char('"');
			}
		}

		FORM_print_char(']');
	}

	FORM_print(")\n");
}
