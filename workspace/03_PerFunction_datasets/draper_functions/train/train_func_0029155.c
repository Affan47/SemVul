partial_glob_match(char *dir, char *pattern)
{
	char buf1[MAXPATHLEN], buf2[MAXPATHLEN];
	char *tmp1, *tmp2;

#ifdef DEBUG
	printf("in partial_glob_match(\"%s\",\"%s\")\n", dir, pattern);
#endif

	strlcat(buf1, dir, sizeof(buf1));
	tmp1 = dirname(buf1);

	strlcat(buf2, pattern, sizeof(buf2));
	if ((tmp2 = strchr(&(buf2[strlen(tmp1) + 1]), '/')) != NULL)
		*tmp2 = '\0';

#ifdef DEBUG
	printf("returning glob_match(\"%s\",\"%s\")\n", dir, buf2);
#endif

	return glob_match(dir, buf2);
}
