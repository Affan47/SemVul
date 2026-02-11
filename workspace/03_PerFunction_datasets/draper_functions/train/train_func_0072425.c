get_password(const char *prompt, char *pass, int length)
{
	int fd = fileno(stdin);
	int count;

	if (isatty(fd)) {
#ifdef HAVE_GETPASS
		const char *s;


		s = getpass(prompt);
		if (s) {
			strncpy(pass, s, length - 1);
			pass[length - 1] = '\0';

			return strlen(pass);
		}
		return -1;
#else
		fprintf(stdout, "%s", prompt);
#endif
	}
	if (fgets(pass, length, stdin)) {

		for (count = 0; pass[count] && pass[count] != '\n'; count++)
			;
		pass[count] = '\0';

		return count;
	}
	return -1;
}
