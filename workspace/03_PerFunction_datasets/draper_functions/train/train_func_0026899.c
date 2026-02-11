ifcmd(void *v)
{
	char **argv = v;
	char *cp;

	if (cond != CANY) {
		printf(catgets(catd, CATSET, 42, "Illegal nested \"if\"\n"));
		return(1);
	}
	cond = CANY;
	cp = argv[0];
	switch (*cp) {
	case 'r': case 'R':
		cond = CRCV;
		break;

	case 's': case 'S':
		cond = CSEND;
		break;

	case 't': case 'T':
		cond = CTERM;
		break;

	default:
		printf(catgets(catd, CATSET, 43,
				"Unrecognized if-keyword: \"%s\"\n"), cp);
		return(1);
	}
	return(0);
}
