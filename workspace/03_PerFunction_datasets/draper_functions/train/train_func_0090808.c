getMultiTabConsoleSwitchCommand(unsigned long *newGnuplotXID)
{

#ifdef HAVE_STRDUP
    char *cmd = NULL;
    char *ptr = getenv("KONSOLE_DCOP_SESSION");
    *newGnuplotXID = 0;
    if (ptr) {


	char *konsole_name = NULL;
	*newGnuplotXID = 0;

	while (1) {
	    char *konsole_tab;
	    unsigned long w;
	    FILE *p;
	    ptr = strchr(ptr, '(');

	    if (!ptr) return NULL;
	    konsole_name = strdup(ptr+1);
	    konsole_tab = strchr(konsole_name, ',');
	    if (!konsole_tab) break;
	    *konsole_tab++ = 0;
	    ptr = strchr(konsole_tab, ')');
	    if (ptr) *ptr = 0;


#ifdef DCOP_RAISE
	    cmd = malloc(2*strlen(konsole_name) + strlen(konsole_tab) + 128);
#else
	    cmd = malloc(strlen(konsole_name) + strlen(konsole_tab) + 64);
#endif
	    sprintf(cmd, "dcop %s konsole-mainwindow#1 getWinID 2>/dev/null", konsole_name);

	    p = popen(cmd, "r");
	    if (p) {
		fscanf(p, "%lu", &w);
		pclose(p);
	    }
	    if (gnuplotXID) {
		if (w != gnuplotXID) break;

	    } else {
		*newGnuplotXID = w;

	    }
#ifdef DCOP_RAISE

	    sprintf(cmd, "dcop %s konsole-mainwindow#1 raise;", konsole_name);
	    sprintf(cmd+strlen(cmd), "dcop %s konsole activateSession %s", konsole_name, konsole_tab);
#else
	    sprintf(cmd, "dcop %s konsole activateSession %s", konsole_name, konsole_tab);
#endif
	    free(konsole_name);
	    return cmd;
	}
	free(konsole_name);
	free(cmd);
	return NULL;
    }


#endif


    return NULL;
}
