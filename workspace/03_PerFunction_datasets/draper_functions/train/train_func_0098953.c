get_range(char *src, int max, const char * const names[], const char *msg)
{
	int start, end;
	unsigned int mask = 0;
	char *part;


	if (ast_strlen_zero(src) || !strcmp(src, "*")) {
		return (1 << max) - 1;
	}

	while ((part = strsep(&src, "&"))) {

		char *endpart = strchr(part, '-');
		if (endpart) {
			*endpart++ = '\0';
		}

		if ((start = lookup_name(part, names, max)) < 0) {
			ast_log(LOG_WARNING, "Invalid %s '%s', skipping element\n", msg, part);
			continue;
		}
		if (endpart) {
			if ((end = lookup_name(endpart, names, max)) < 0) {
				ast_log(LOG_WARNING, "Invalid end %s '%s', skipping element\n", msg, endpart);
				continue;
			}
		} else {
			end = start;
		}

		mask |= (1 << end);
		while (start != end) {
			mask |= (1 << start);
			if (++start >= max) {
				start = 0;
			}
		}
	}
	return mask;
}
