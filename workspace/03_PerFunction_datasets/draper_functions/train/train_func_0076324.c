dighost_shutdown(void) {
	char batchline[MXNAME];
	int bargc;
	char *bargv[16];
	char *input;
	int i;

	if (batchname == NULL) {
		isc_app_shutdown();
		return;
	}

	fflush(stdout);
	if (feof(batchfp)) {
		batchname = NULL;
		isc_app_shutdown();
		if (batchfp != stdin)
			fclose(batchfp);
		return;
	}

	if (fgets(batchline, sizeof(batchline), batchfp) != 0) {
		debug("batch line %s", batchline);
		bargc = 1;
		input = batchline;
		bargv[bargc] = next_token(&input, " \t\r\n");
		while ((bargv[bargc] != NULL) && (bargc < 14)) {
			bargc++;
			bargv[bargc] = next_token(&input, " \t\r\n");
		}

		bargv[0] = argv0;

		for(i = 0; i < bargc; i++)
			debug("batch argv %d: %s", i, bargv[i]);
		parse_args(ISC_TRUE, ISC_FALSE, bargc, (char **)bargv);
		start_lookup();
	} else {
		batchname = NULL;
		if (batchfp != stdin)
			fclose(batchfp);
		isc_app_shutdown();
		return;
	}
}
