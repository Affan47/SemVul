dectobin (uae_u32 val)
{
	char *s = (char *)malloc(sizeof(char));
	if (s == NULL) {
		fprintf(stderr, "Not enough memory!");
		exit(-1);
	}

	while (val)
	{
		char *ps = strdup(s);
		if (ps == NULL) {
			fprintf(stderr, "Not enough memory!");
			exit(-1);
		}
		free(s);
		s = (char *)malloc((strlen(ps) + 2) * sizeof(char));
		if (s == NULL) {
			fprintf(stderr, "Not enough memory!");
			exit(-1);
		}
		s[0] = val % 2 + '0';
		val /= 2;
		strcpy(s + 1, ps);
		free(ps);
	}
	return s;
}
