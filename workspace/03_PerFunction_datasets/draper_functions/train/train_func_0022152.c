ProgName (progpath0)

char *progpath0;
{
    char *progpath, *progname;
    int i, lpath;

    lpath = (strlen (progpath0) + 2) / 8;
    lpath = (lpath + 1) * 8;;
    progpath = (char *) calloc (lpath, 1);
    strcpy (progpath, progpath0);
    progname = progpath;
    for (i = strlen (progpath); i > -1; i--) {
        if (progpath[i] > 63 && progpath[i] < 90)
            progpath[i] = progpath[i] + 32;
        if (progpath[i] == '/') {
            progname = progpath + i + 1;
            break;
            }
	}
    return (progname);
}
