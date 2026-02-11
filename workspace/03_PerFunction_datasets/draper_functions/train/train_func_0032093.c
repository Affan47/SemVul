ungroup(void *v)
{
	char **argv = v;

	if (*argv == NULL) {
		printf(catgets(catd, CATSET, 209,
				"Must specify alias or group to remove\n"));
		return 1;
	}
	do
		remove_group(*argv);
	while (*++argv != NULL);
	return 0;
}
