main (int argc, char *argv[]) {
    long t;
    struct tm *eris;
    int bob,raw;
    struct disc_time hastur;
    char schwa[23*17], *fnord=0;
    int pi;
    char *progname, *p;

    progname = argv[0];
    if ((p = strrchr(progname, '/')) != NULL)
	progname = p+1;

    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    srandom(time(NULL));

    for(pi=1; pi<argc; pi++) {
	switch(argv[pi][0]) {
	case '+': fnord=argv[pi]+1; break;
	case '-':
	    switch(argv[pi][1]) {
	    case 'V':
		printf(_("%s (%s)\n"), progname, PACKAGE_STRING);
	    default: goto usage;
	    }
	default: goto thud;
	}
    }

  thud:
    if (argc-pi==3){
	int moe=atoi(argv[pi]), larry=atoi(argv[pi+1]), curly=atoi(argv[pi+2]);
	hastur=makeday(
#ifdef US_FORMAT
	    moe,larry,
#else
	    larry,moe,
#endif
	    curly);
	if (hastur.season == -1) {
		printf("Invalid date -- out of range\n");
		return -1;
	}
	fnord=fnord?fnord:default_fmt;
    } else if (argc!=pi) {
      usage:
	fprintf(stderr,_("usage: %s [+format] [day month year]\n"), argv[0]);
	exit(1);
    } else {
	t= time(NULL);
	eris=localtime(&t);
	bob=eris->tm_yday;
	raw=eris->tm_year;
	hastur=convert(bob,raw);
	fnord=fnord?fnord:default_immediate_fmt;
    }
    format(schwa, fnord, hastur);
    printf("%s\n", schwa);

    return 0;
}
