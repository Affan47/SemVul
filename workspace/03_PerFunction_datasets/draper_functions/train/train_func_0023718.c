progress_update(dl_progress_t *dpp, size_t add_bytes)
{
	dpp->dp_bytecount += add_bytes;

	if (dl_verbose
	    && isatty(fileno(stdout))
	    && dpp->dp_bytecount > dpp->dp_nextreport)
	{
		printf("    * received %lu", (unsigned long)dpp->dp_bytecount);
		if (dpp->dp_total != 0)
			printf("/%lu", (unsigned long)dpp->dp_total);
		printf(" bytes\r");
		fflush(stdout);
		dpp->dp_nextreport += DL_PROGRESS_INTERVAL;
	}
}
