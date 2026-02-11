is_ISDN_on (glibtop *server, int *online)
{
	FILE *f = NULL;
	char buffer [BUFSIZ], *p;
	int i;


	f = fopen ("/dev/isdninfo", "r");

	if (!f) return FALSE;

	for (i = 0; i < 5; i++) {
		if (fgets (buffer, BUFSIZ, f) == NULL) {
			fclose (f);
			return FALSE;
		}
	}

	if (strncmp (buffer, "flags:", 6)) {
		fclose (f);
		return FALSE;
	}

	p = buffer+6;

	while (*p) {
		char *end = p;

		if (isspace (*p)) {
			p++;
			continue;
		}

		for (end = p; *end && !isspace (*end); end++)
			;

		if (*end == 0)
			break;
		else
			*end = 0;

		if (!strcmp (p, "?") || !strcmp (p, "0")) {
			p = end+1;
			continue;
		}

		fclose (f);

		*online = TRUE;
		return TRUE;
	}

	fclose (f);

	*online = FALSE;
	return TRUE;
}
