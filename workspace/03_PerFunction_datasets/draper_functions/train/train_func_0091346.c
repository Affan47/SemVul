getswitchvaluelist(char *arg, int *pj, int list[], char delim[],
		   int limit, int *count, char *sep)


{
    int j,val;
    int go;
    char *strchr();

    *count = 0;
    j = *pj + 1;

    go = TRUE;
    delim[0] = arg[*pj];

    while (go)
    {
	if (*count >= limit)
	{
	    fprintf(stderr,
		    ">E %s: too many values for -%c\n",cmdname,arg[*pj]);
	    exit(1);
	}

	val = 0;
	while (arg[j] >= '0' && arg[j] <= '9')
	{
	    val = val * 10 + (arg[j] - '0');
	    ++j;
	}
        list[(*count)++] = val;

	if (arg[j] != '\0' && strchr(sep,arg[j]))
	    delim[*count] = arg[j++];
        else
            go = FALSE;
    }

    *pj = j - 1;
}
