sfh_argv_add(int *argc, char ***argv, char *arg)
{


	if (*argv == 0) {
		*argv = (char **) malloc(2 * sizeof(char *));
		if (*argv == 0) return(-1);
		(*argv)[0] = 0;
		(*argv)[1] = 0;
	}


	else {
		*argv = (char **) realloc((char *) *argv,
				(unsigned) (*argc + 2) * sizeof(char *));
		if (*argv == 0) return(-1);
	}

	(*argv)[*argc] = (char*) malloc((unsigned) strlen(arg) + 1);
	if ((*argv)[*argc] == 0) return(-1);

	strcpy((*argv)[*argc], arg);
	*argc = *argc + 1;
	(*argv)[*argc] = 0;
	return(0);
}
