string_split(char *str, int *argc, char ***argv)
{
	*argc = 0;

	*argv = malloc((strlen(str) + 1) * sizeof(char *));
	if(!*argv)
		return 0;

	while(*str) {
		while(isspace((int) *str)) {
			str++;
		}
		(*argv)[(*argc)++] = str;
		while(*str && !isspace((int) *str)) {
			str++;
		}
		if(*str) {
			*str = 0;
			str++;
		}
	}

	(*argv)[*argc] = 0;

	return 1;
}
