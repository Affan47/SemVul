main_compile (void) {
      if (app_argc < 4)
	MAIN_INV_CMD_SYNTAX;

      writerco_options opts;

      char *sXmlFile = NULL;
      char *sRcoFile = NULL;

      uint8_t sNoConvGim = FALSE;
      uint8_t sNoConvVag = FALSE;
      uint8_t sNoConvVsmx = FALSE;
      RcoDumpGimconvOpts gimconvOpts;

      gimconvOpts.cmd = gimconvOpts.extFlags = NULL;

      int i;


      get_pack_opts (&opts);
      retrieve_from_opts (TRUE, 5, "--no-convgim", "bool", &sNoConvGim,
	  "--no-convvag", "bool", &sNoConvVag, "--no-encvsmx", "bool",
	  &sNoConvVsmx, "--gimconv-cmd", "text", &gimconvOpts.cmd,
	  "--gimconv-flags", "text", &gimconvOpts.extFlags);

      for (i = 2; i < app_argc; i++) {
	if (!app_argv[i])
	  continue;
	if (!sXmlFile)
	  sXmlFile = app_argv[i];
	else if (!sRcoFile)
	  sRcoFile = app_argv[i];
	else
	  MAIN_INV_CMD_SYNTAX}

	if (!sRcoFile || !sXmlFile)
	  MAIN_INV_CMD_SYNTAX rRCOFile *rco = read_xml (sXmlFile);

	if (!rco) {
	  error ("Could not read in XML file '%s'.", sXmlFile);
	  return RETERR_READXML;
	}

	if (!sNoConvGim) {
	  rco_map_func (rco, NULL, (void *) &gimconvOpts, compile_gimconv_map);
	}
	if (!sNoConvVag) {
	  rco_map_func (rco, NULL, NULL, compile_vagconv_map);
	} else
	  rco_map_func (rco, NULL, NULL, compile_wavcheck_map);


	if (!sNoConvVsmx) {
	  rco_map_func (rco, NULL, NULL, compile_vsmxconv_map);
	}

	if (!write_rco (rco, sRcoFile, opts))
	  return RETERR_WRITERCO;

	return 0;
      }
