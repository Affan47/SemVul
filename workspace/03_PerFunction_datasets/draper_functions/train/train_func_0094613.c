do_slashslash ()
    {
    int			c;

    putchar (' ');

    while ((c = igetchar ()) != EOF)
	{
	putchar (c);
	if (c == '\n')
	    return 0;
	}

    return 1;
    }
