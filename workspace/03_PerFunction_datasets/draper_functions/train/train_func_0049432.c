strip_comments(char *line, int in_quotes)
{
	int quote_count = in_quotes;
	char *ptr;

	for (ptr = line; *ptr; ++ptr) {
		if (ptr[0] == '"' && ptr > line && ptr[-1] != '\\')
			quote_count++;

		if ((ptr[0] == ';' || ptr[0] == '#') && (quote_count % 2) == 0) {
			ptr[0] = '\0';
			break;
		}
	}


	if (ptr > line && git__isspace(ptr[-1])) {
		ptr--;
	}
	ptr[0] = '\0';

	return quote_count;
}
