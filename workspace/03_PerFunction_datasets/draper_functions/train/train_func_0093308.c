do_slashstar ()
    {
    int			c;

    putchar (' ');

    while ((c = igetchar ()) != EOF)
	{
	if (c != '*')
	    putchar (c);
	else
	    {
	    if ((c = igetchar ()) == EOF)
		return 1;
	    if (c == '/')
		{
		putchar (' ');
		putchar (' ');
		return 0;
		}
	    putchar ('*');
	    putchar (c);
	    }
	}

    return 1;
    }
