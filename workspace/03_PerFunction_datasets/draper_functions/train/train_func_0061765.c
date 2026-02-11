openF(char *fname, char *mode)
{
    FILE *f = fopen(fname, mode);
    if (!f) {
	fprintf(stderr, "Could not open %s for %s\n", fname,
		((*mode == 'r') ? "reading" : "writing"));
	exit(1);
    }
    return f;
}
