CRASHPAGER_valid(void)
{
	int i, c;
	char *env, *CRASHPAGER_buf;
	char *arglist[MAXARGS];

	if (CRASHPAGER_argv)
		return TRUE;

	if (!(env = getenv("CRASHPAGER")))
		return FALSE;

	if (strstr(env, "|") || strstr(env, "<") || strstr(env, ">")) {
		error(INFO,
		    "CRASHPAGER ignored: contains invalid character: \"%s\"\n",
			env);
		return FALSE;
	}

	if ((CRASHPAGER_buf = (char *)malloc(strlen(env)+1)) == NULL)
		return FALSE;

	strcpy(CRASHPAGER_buf, env);

	if (!(c = parse_line(CRASHPAGER_buf, arglist)) ||
	    !file_exists(arglist[0], NULL) || access(arglist[0], X_OK) ||
	    !(CRASHPAGER_argv = (char **)malloc(sizeof(char *) * (c+1)))) {
		free(CRASHPAGER_buf);
		if (strlen(env))
			error(INFO,
		    		"CRASHPAGER ignored: \"%s\"\n", env);
		return FALSE;
	}

	for  (i = 0; i < c; i++)
		CRASHPAGER_argv[i] = arglist[i];
	CRASHPAGER_argv[i] = NULL;

	return TRUE;
}
