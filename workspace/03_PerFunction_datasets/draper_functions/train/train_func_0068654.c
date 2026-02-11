command (char *fmt,...)
{
    va_list ap;
    int r;
    sighand oldintr;

    abrtflag = 0;
    if (cout == NULL) {
	warn ("No control connection for command");
	code = -1;
	return (0);
    }
    oldintr = signal(SIGINT, cmdabort);
    if(debug){
	printf("---> ");
	if (strncmp("PASS ", fmt, 5) == 0)
	    printf("PASS XXXX");
	else {
	    va_start(ap, fmt);
	    vfprintf(stdout, fmt, ap);
	    va_end(ap);
	}
    }
    va_start(ap, fmt);
    sec_vfprintf(cout, fmt, ap);
    va_end(ap);
    if(debug){
	printf("\n");
	fflush(stdout);
    }
    fprintf (cout, "\r\n");
    fflush (cout);
    cpend = 1;
    r = getreply (!strcmp (fmt, "QUIT"));
    if (abrtflag && oldintr != SIG_IGN)
	(*oldintr) (SIGINT);
    signal (SIGINT, oldintr);
    return (r);
}
