prc_parse_file (const char *pathname, const flag securecheck)

{
    prc_errflag = 0;
    querylist = hosttail = (struct query *)NULL;

    errno = 0;


    if ( (prc_errflag = prc_filecheck(pathname, securecheck)) != 0 )
	return(prc_errflag);


    if (errno == ENOTDIR)
	return(PS_IOERR);
    else if (errno == ENOENT)
	return(PS_SUCCESS);


    if (strcmp(pathname, "-") == 0)
	yyin = stdin;
    else if ((yyin = fopen(pathname,"r")) == (FILE *)NULL) {
	report(stderr, "open: %s: %s\n", pathname, strerror(errno));
	return(PS_IOERR);
    }

    yyparse();

    if (yyin != stdin)
       fclose(yyin);

    if (prc_errflag)
	return(PS_SYNTAX);
    else
	return(PS_SUCCESS);
}
