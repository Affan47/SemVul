main_rebuild (void) {
	if (app_argc < 4)
	  MAIN_INV_CMD_SYNTAX;

	writerco_options opts;

	char *sRcoFileIn = NULL;
	char *sRcoFileOut = NULL;

	int i;


	get_pack_opts (&opts);
	for (i = 2; i < app_argc; i++) {
	  if (!app_argv[i])
	    continue;
	  if (!sRcoFileIn)
	    sRcoFileIn = app_argv[i];
	  else if (!sRcoFileOut)
	    sRcoFileOut = app_argv[i];
	  else
	    MAIN_INV_CMD_SYNTAX}

	    rRCOFile *rco = read_rco (sRcoFileIn);

	  if (!rco)
	    return RETERR_READRCO;

	  if (!write_rco (rco, sRcoFileOut, opts))
	    return RETERR_WRITERCO;

	  return 0;
	}
