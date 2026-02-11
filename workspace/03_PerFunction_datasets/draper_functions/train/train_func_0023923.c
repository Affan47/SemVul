applydir(dir, funcf, funcd1, funcd2, order, endmes)
CONST char *dir;
int (*funcf)__P_((CONST char *));
int (*funcd1)__P_((CONST char *));
int (*funcd2)__P_((CONST char *));
int order;
CONST char *endmes;
{
	char path[MAXPATHLEN];
	int verbose;

	verbose = 1;
	if (!dir) {
		dir = curpath;
		verbose = 0;
	}
	else if (isdotdir(dir) == 1) {
		Xrealpath(dir, path, 0);
		dir = path;
	}
#ifdef	DEP_DOSEMU
	else dir = nodospath(path, dir);
#endif

	return(_applydir(dir, funcf, funcd1, funcd2, order, endmes, verbose));
}
