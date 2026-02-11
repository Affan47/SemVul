parse_arguments (GkmModule *self, const gchar *string)
{
	gchar quote = '\0';
	gchar *src, *dup, *at, *arg;

	g_assert (GKM_IS_MODULE (self));

	if (!string)
		return;

	src = dup = g_strdup (string);

	arg = at = src;
	for (src = dup; *src; src++) {


		if (quote == *src) {
			quote = '\0';


		} else if (quote != '\0') {
			if (*src == '\\') {
				*at++ = *src++;
				if (!*src) {
					g_warning ("couldn't parse module argument string");
					goto done;
				}
				if (*src != quote)
					*at++ = '\\';
			}
			*at++ = *src;


		} else if (g_ascii_isspace(*src)) {
			*at = 0;
			parse_argument (self, arg);
			arg = at;


		} else {
			switch (*src) {
			case '\'':
			case '"':
				quote = *src;
				break;
			case '\\':
				*at++ = *src++;
				if (!*src) {
					g_warning ("couldn't parse module argument string");
					goto done;
				}

			default:
				*at++ = *src;
				break;
			}
		}
	}


	if (at != arg) {
		*at = 0;
		parse_argument (self, arg);
	}

done:
	g_free (dup);
}
