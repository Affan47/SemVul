mkdict(fp)
FILE *fp;
{
	if (fputheader("headers", fp) < 0) return(-1);
	if (nocontent) return(0);

	if (verbose) {
		fprintf(stdout, "writing...");
		fflush(stdout);
	}

	if (writeindex(fp) < 0) return(-1);
	if (writedict(fp) < 0) return(-1);

	if (genconlist() < 0) return(-1);
	if (writehinsiindex(fp) < 0) return(-1);
	if (writehinsidict(fp) < 0) return(-1);

	if (verbose) fputs("  done.\n", stdout);

	return(0);
}
