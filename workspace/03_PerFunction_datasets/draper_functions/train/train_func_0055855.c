main(int argc, char **argv)
{
    CONDITION
    cond;
    short
        dbid;
    CTNBOOLEAN
	prepend = FALSE;
    static char dbfile[MAXFILENAME];
    static char imgfile[MAXFILENAME];
    static char prefmtImgfile[MAXFILENAME];

    THR_Init();
    (void) strcpy(cwd, "\0");


    if (!getcwd(cwd, sizeof(cwd)))
	myExit(GETWDERROR);


    while (--argc > 0 && (*++argv)[0] == '-') {
	switch (*(argv[0] + 1)) {
	case 'v':
	    verbose = TRUE;
	    break;
	case 'p':
	    prepend = TRUE;
	    break;
	default:
	    myExit(UNKNOWNCMDLINEARG);
	}
    }
    if (argc < 3)
	usageError();

    if (sscanf(*argv++, "%s", dbfile) != 1)
	usageError();


    if (prepend) {
	(void) sprintf(imgfile, "%s/%s", cwd, *argv++);
	(void) sprintf(prefmtImgfile, "%s/%s", cwd, *argv++);
    } else {
	(void) sprintf(imgfile, "%s", *argv++);
	(void) sprintf(prefmtImgfile, "%s", *argv++);
    }

    if (verbose)
	printf("DB file : %s, imgfile : %s, prefmtfile : %s\n", dbfile,
	       imgfile, prefmtImgfile);


    cond = DB_Open(dbfile, &dbid);
    if (cond != DB_NORMAL) {

	cond = DB_CreateDB(dbfile);
	if (cond != DB_NORMAL)
	    myExit(DBCREATEERROR);

	cond = DB_Open(dbfile, &dbid);
	if (cond != DB_NORMAL)
	    myExit(DBOPENERROR);
    }

    if (!access(imgfile, R_OK))
	makeDBEntry(dbid, imgfile, prefmtImgfile);
    else
	myExit(NOREADACCESSERROR);

    THR_Shutdown();
    return (0);
}
