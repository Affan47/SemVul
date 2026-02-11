CCreaders(char *av[])
{
    const char	*p;

    switch (av[0][0]) {
    default:
	return "1 Bad flag";
    case 'y':
	if (NNRPReason == NULL)
	    return "1 Already allowing readers";
	p = av[1];
	if (*p && strcmp(p, NNRPReason) != 0)
	    return "1 Wrong reason";
	free(NNRPReason);
	NNRPReason = NULL;
	break;
    case 'n':
	if (NNRPReason)
	    return "1 Already not allowing readers";
	p = av[1];
	if (*p == '\0')
	    return CCnoreason;
	if (strlen(p) > MAX_REASON_LEN)
	    return CCbigreason;
        if (!is_valid_utf8(p))
            return "1 Invalid UTF-8 reason";
	NNRPReason = xstrdup(p);
	break;
    }
    return NULL;
}
