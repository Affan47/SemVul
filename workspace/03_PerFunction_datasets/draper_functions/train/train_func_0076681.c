CMDxover(ac, av)
    int			ac;
    char		*av[];
{
    register char	*p;
    register ARTNUM	i;
    register BOOL	Opened;
    ARTRANGE		range;
    char		buff[SPOOLNAMEBUFF];

    if (!PERMcanread) {
	Printf("%s\r\n", NOACCESS);
	return;
    }


    if (GRPcount == 0) {
	Reply("%s\r\n", ARTnotingroup);
	return;
    }


    if (!CMDgetrange(ac, av, &range))
	return;

    Reply("%d data follows\r\n", NNTP_OVERVIEW_FOLLOWS_VAL);
    for (Opened = OVERopen(), i = range.Low; i <= range.High; i++) {
	if (ARTfind(i) < 0)
	    continue;


	if (Opened && (p = OVERfind(i)) != NULL) {
#ifdef OVERSCREAM
	    char* eol = memchr(p, '\n', OVERsize - (p - OVERshm));
	    if ( eol == NULL )
		continue;
	    fwrite(p, 1, eol - p, stdout);
	    fwrite("\r\n", 1, 2, stdout);
#else
	    Printf("%s\r\n", p);
#endif
	    continue;
	}

	(void)sprintf(buff, "%ld", i);

	if ((p = OVERgen(buff)) != NULL)
	    Printf("%s\r\n", p);
    }
    Printf(".\r\n");
}
