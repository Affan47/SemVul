opt_dpi(const char *opt, const char *myoptarg, void *client_data)
{
    char *field;
    PLFLT xdpi = 0., ydpi = 0.;
    PLINT xwid = 0, ywid = 0, xoff = 0, yoff = 0;

    (void) opt;
    (void) client_data;

    strncpy(opttmp, myoptarg, OPTMAX-1);
    if (strchr (opttmp, 'x')) {
	field = strtok (opttmp, "x");
	xdpi = atof (field);
	if (xdpi == 0)
	    fprintf (stderr, "?invalid xdpi\n");

	if ((field = strtok (NULL, " ")) == NULL)
	   return 1;

        ydpi = atof (field);
        if (ydpi == 0)
	   fprintf (stderr, "?invalid ydpi\n");

    } else {
	xdpi = atof (opttmp);
	ydpi=xdpi;
	if (xdpi==0) return 1;
    }

    plspage (xdpi, ydpi, xwid, ywid, xoff, yoff);
    return 0;
}
