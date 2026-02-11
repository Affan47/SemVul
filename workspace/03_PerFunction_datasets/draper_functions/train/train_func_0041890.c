defFont(FILE* fd, TextCoord ps, bool useISO8859) const
{
    if (useISO8859) {
	fprintf(fd, defISOFont, (const char*) setproc,
	    (const char*) family, (const char*) family, ps/20, ps/20);
    } else {
	fprintf(fd, defRegularFont, (const char*) setproc,
	    (const char*) family, ps/20);
    }
    fprintf(fd, "/%s{%s show}def\n",
	(const char*) showproc, (const char*) setproc);
}
