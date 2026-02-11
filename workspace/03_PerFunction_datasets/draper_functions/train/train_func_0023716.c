split_line_zoo (char *line)
{
	char       **fields;
	const char  *scan, *field_end;
	int          i;

	if (line[0] == '-') {
		return NULL;
	}

	fields = g_new0 (char *, 6);
	fields[5] = NULL;


	scan = _g_str_eat_spaces (line);
	field_end = strchr (scan, ' ');
	fields[0] = g_strndup (scan, field_end - scan);
	scan = _g_str_eat_spaces (field_end);


	for (i = 0; i < 2; i++) {
		field_end = strchr (scan, ' ');
		scan = _g_str_eat_spaces (field_end);
	}


	for (i = 1; i < 5; i++) {
		if (i == 2 && g_ascii_strncasecmp (scan, "file", 4) == 0) {
			g_strfreev(fields);
			return NULL;
		}
		field_end = strchr (scan, ' ');
		fields[i] = g_strndup (scan, field_end - scan);
		scan = _g_str_eat_spaces (field_end);
	}

	return fields;
}
