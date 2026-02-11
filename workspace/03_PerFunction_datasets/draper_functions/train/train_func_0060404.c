tbldump (flagp, numflags)
    register struct flagent *	flagp;
    register int		numflags;
    {

    while (--numflags >= 0)
	entdump (flagp++);
    }
