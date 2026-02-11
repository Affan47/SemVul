get_response(unsigned char* prompt)
{
	FILE* tty = NULL;
	unsigned char* response = NULL;

	char buf[DROPBEAR_MAX_CLI_PASS];
	char* ret = NULL;

	fprintf(stderr, "%s", prompt);

	tty = fopen(_PATH_TTY, "r");
	if (tty) {
		ret = fgets(buf, sizeof(buf), tty);
		fclose(tty);
	} else {
		ret = fgets(buf, sizeof(buf), stdin);
	}

	if (ret == NULL) {
		response = (unsigned char*)m_strdup("");
	} else {
		unsigned int buflen = strlen(buf);

		if (buflen > 0 && buf[buflen-1] == '\n')
			buf[buflen-1] = '\0';
		response = (unsigned char*)m_strdup(buf);
	}

	m_burn(buf, sizeof(buf));

	return response;
}
