do_info(const char *file, int FAST_FUNC (*proc)(char *))
{
	int lnr;
	FILE *procinfo;
	char *buffer;


	procinfo = fopen_or_warn_stdin(file);
	if (procinfo == NULL) {
		return;
	}
	lnr = 0;

	while ((buffer = xmalloc_fgets_str(procinfo, "\n")) != NULL) {

		if (lnr && proc(buffer))
			bb_error_msg("%s: bogus data on line %d", file, lnr + 1);
		lnr++;
		free(buffer);
	}
	fclose(procinfo);
}
