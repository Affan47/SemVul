compact_range_list(CELL negmin, CELL negmax, CELL zero, CELL posmin,
		       CELL posmax, CELL null, char *no_data_str,
		       int skip_nulls)
{
    if (negmin) {
	fprintf(stdout, "%ld", (long)negmin);
	if (negmin != negmax)
	    fprintf(stdout, " thru %ld", (long)negmax);
	fprintf(stdout, "\n");
    }
    if (zero)
	fprintf(stdout, "0\n");
    if (posmin) {
	fprintf(stdout, "%ld", (long)posmin);
	if (posmin != posmax)
	    fprintf(stdout, " thru %ld", (long)posmax);
	fprintf(stdout, "\n");
    }

    if (null && !skip_nulls)
	fprintf(stdout, "%s\n", no_data_str);

    return (0);
}
