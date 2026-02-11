dtol(char *s, int flags, int *errptr)
{
        ulong retval;
        char *p, *orig;
        int j;

        if (s == NULL) {
		if (!(flags & QUIET))
                	error(INFO, "received NULL string\n");
                goto dtol_error;
        }

	if (strlen(s) == 0)
                goto dtol_error;

        p = orig = &s[0];
        while (*p++ == ' ')
                s++;

        for (j = 0; s[j] != '\0'; j++)
                if ((s[j] < '0' || s[j] > '9'))
                        break ;

	if (s[j] != '\0') {
		if (!(flags & QUIET))
                	error(INFO, "%s: \"%c\" is not a digit 0 - 9\n",
				orig, s[j]);
                goto dtol_error;
	} else if (sscanf(s, "%lu", &retval) != 1) {
		if (!(flags & QUIET))
                	error(INFO, "invalid expression\n");
                goto dtol_error;
        }

        return(retval);

dtol_error:
        switch (flags & (FAULT_ON_ERROR|RETURN_ON_ERROR))
        {
        case FAULT_ON_ERROR:
                RESTART();

        case RETURN_ON_ERROR:
		if (errptr)
			*errptr = TRUE;
                break;
        }

	return UNUSED;
}
