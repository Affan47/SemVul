force_page_size(char *s)
{
	int k, err;
	ulong psize;

	k = 1;
	err = FALSE;
	psize = 0;

	switch (LASTCHAR(s))
	{
	case 'k':
	case 'K':
		LASTCHAR(s) = NULLCHAR;
		if (!decimal(s, 0)) {
			err = TRUE;
			break;
		}
		k = 1024;


	default:
        	if (decimal(s, 0))
                	psize = dtol(s, QUIET|RETURN_ON_ERROR, &err);
        	else if (hexadecimal(s, 0))
                	psize = htol(s, QUIET|RETURN_ON_ERROR, &err);
		else
			err = TRUE;
		break;
	}

	if (err)
		error(INFO, "invalid page size: %s\n", s);
	else
		machdep->pagesize = psize * k;
}
