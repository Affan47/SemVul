_find_quote_token(char *tmp, char *sep, char **last)
{
	char *start, *quote_single = 0, *quote_double = 0;
	int i;

	xassert(last);
	if (*last)
		start = *last;
	else
		start = tmp;
	if (start[0] == '\0')
		return NULL;
	for (i = 0; ; i++) {
		if (start[i] == '\'') {
			if (quote_single)
				quote_single--;
			else
				quote_single++;
		} else if (start[i] == '\"') {
			if (quote_double)
				quote_double--;
			else
				quote_double++;
		} else if (((start[i] == sep[0]) || (start[i] == '\0')) &&
			   (quote_single == 0) && (quote_double == 0)) {
			if (((start[0] == '\'') && (start[i-1] == '\'')) ||
			    ((start[0] == '\"') && (start[i-1] == '\"'))) {
				start++;
				i -= 2;
			}
			if (start[i] == '\0')
				*last = &start[i];
			else
				*last = &start[i] + 1;
			start[i] = '\0';
			return start;
		} else if (start[i] == '\0') {
			error("Improperly formed environment variable (%s)",
			      start);
			*last = &start[i];
			return start;
		}

	}
}
