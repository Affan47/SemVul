arg_all()
{
    int		len;
    int		idx;
    char_u	*retval = NULL;
    char_u	*p;


    for (;;)
    {
	len = 0;
	for (idx = 0; idx < ARGCOUNT; ++idx)
	{
	    p = alist_name(&ARGLIST[idx]);
	    if (p != NULL)
	    {
		if (len > 0)
		{

		    if (retval != NULL)
			retval[len] = ' ';
		    ++len;
		}
		for ( ; *p != NUL; ++p)
		{
		    if (*p == ' ' || *p == '\\')
		    {

			if (retval != NULL)
			    retval[len] = '\\';
			++len;
		    }
		    if (retval != NULL)
			retval[len] = *p;
		    ++len;
		}
	    }
	}


	if (retval != NULL)
	{
	    retval[len] = NUL;
	    break;
	}


	retval = alloc((unsigned)len + 1);
	if (retval == NULL)
	    break;
    }

    return retval;
}
