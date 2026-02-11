isme(const char *identifier,
		void *void_arg)
{
	struct computeinfo *ci=(struct computeinfo *)void_arg;
	int i;

	for (i=4; i<ci->argc; i++)
		if (strcmp(ci->argv[i], identifier) == 0)
			return 1;
	return 0;
}
