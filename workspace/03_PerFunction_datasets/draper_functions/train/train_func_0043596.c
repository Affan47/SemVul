lak_tokenize_domains(
	const char *d,
	int n,
	char **result)
{
	char *s, *s1;
	char *lasts;
	int nt, i, rc;

	*result = NULL;

	if (d == NULL || n < 1 || n > 9)
		return LAK_FAIL;

	s = strdup(d);
	if (s == NULL)
		return LAK_NOMEM;

	for( nt=0, s1=s; *s1; s1++ )
		if( *s1 == '.' ) nt++;
	nt++;

	if (n > nt) {
		free(s);
		return LAK_FAIL;
	}

	i = nt - n;
	s1 = (char *)strtok_r(s, ".", &lasts);
	while(s1) {
		if (i == 0) {
			rc = lak_escape(s1, strlen(s1), result);
			free(s);
			return rc;
		}
		s1 = (char *)strtok_r(NULL, ".", &lasts);
		i--;
	}

	free(s);
	return LAK_FAIL;
}
