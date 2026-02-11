parse_arguments (const char *string)
{
	char quote = '\0';
	char *src, *dup, *at, *arg;

	if (!string)
		return;

	src = dup = strdup (string);
	if (!dup) {
		warning (("couldn't allocate memory for argument string"));
		return;
	}

	arg = at = src;
	for (src = dup; *src; src++) {


		if (quote == *src) {
			quote = '\0';


		} else if (quote != '\0') {
			if (*src == '\\') {
				*at++ = *src++;
				if (!*src) {
					warning (("couldn't parse argument string: %s", string));
					goto done;
				}
				if (*src != quote)
					*at++ = '\\';
			}
			*at++ = *src;


		} else if (isspace(*src)) {
			*at = 0;
			parse_argument (arg);
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
					warning (("couldn't parse argument string: %s", string));
					goto done;
				}

			default:
				*at++ = *src;
				break;
			}
		}
	}


	if (at != arg)
		parse_argument (arg);

done:
	free (dup);
}
