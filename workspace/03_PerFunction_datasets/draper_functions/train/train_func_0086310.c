get_security_password (int handle_NULL)
{
	unsigned int maxlen = sizeof(security_password) - 1;

	if (argc < 2) {
		fprintf(stderr, "missing PASSWD\n");
		exit(EINVAL);
	}
	argp = *argv++, --argc;
	if (!argp) {
		fprintf(stderr, "missing PASSWD\n");
		exit(EINVAL);
	}
	if (strlen(argp) > maxlen) {
		fprintf(stderr, "PASSWD too long (must be %d chars max)\n", maxlen);
		exit(EINVAL);
	}
	memset(security_password, 0, maxlen + 1);
	if (!handle_NULL || strcmp(argp, "NULL"))
		strcpy(security_password, argp);
	printf("security_password=\"%s\"\n", security_password);
	while (*argp)
		++argp;
}
