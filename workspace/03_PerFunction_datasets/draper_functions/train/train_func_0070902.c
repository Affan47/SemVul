eel_str_double_underscores (const char *string)
{
	int underscores;
	const char *p;
	char *q;
	char *escaped;

	if (string == NULL) {
		return NULL;
	}

	underscores = 0;
	for (p = string; *p != '\0'; p++) {
		underscores += (*p == '_');
	}

	if (underscores == 0) {
		return g_strdup (string);
	}

	escaped = g_new (char, strlen (string) + underscores + 1);
	for (p = string, q = escaped; *p != '\0'; p++, q++) {

		if (*p == '_') {
			*q++ = '_';
		}
		*q = *p;
	}
	*q = '\0';

	return escaped;
}
