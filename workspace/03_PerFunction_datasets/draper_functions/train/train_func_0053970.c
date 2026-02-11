plGetFlt(char *s)
{
    PLFLT m;
    double m1;
    int i = 0;
    char line[256];

    while (i++ < 10) {
	fprintf(stdout, "%s", s);
	plio_fgets(line, sizeof(line), stdin);

#ifdef MSDOS
	m = atof(line);
	return (m);
#else
	if (sscanf(line, "%lf", &m1) == 1) {
	    m = (PLFLT) m1;
	    return (m);
	}
	fprintf(stdout, "No value or value out of range; please try again\n");
#endif
    }
    plexit("Too many tries.");
    return (0.);
}
