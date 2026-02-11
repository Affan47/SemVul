diff_setup_done(struct diff_options *options)
{
	int count = 0;

	if (options->output_format & DIFF_FORMAT_NAME)
		count++;
	if (options->output_format & DIFF_FORMAT_NAME_STATUS)
		count++;
	if (options->output_format & DIFF_FORMAT_CHECKDIFF)
		count++;
	if (options->output_format & DIFF_FORMAT_NO_OUTPUT)
		count++;
	if (count > 1)
		die("--name-only, --name-status, --check and -s are mutually exclusive");

	if (options->find_copies_harder)
		options->detect_rename = DIFF_DETECT_COPY;

	if (options->output_format & (DIFF_FORMAT_NAME |
				      DIFF_FORMAT_NAME_STATUS |
				      DIFF_FORMAT_CHECKDIFF |
				      DIFF_FORMAT_NO_OUTPUT))
		options->output_format &= ~(DIFF_FORMAT_RAW |
					    DIFF_FORMAT_NUMSTAT |
					    DIFF_FORMAT_DIFFSTAT |
					    DIFF_FORMAT_SHORTSTAT |
					    DIFF_FORMAT_SUMMARY |
					    DIFF_FORMAT_PATCH);


	if (options->output_format & (DIFF_FORMAT_PATCH |
				      DIFF_FORMAT_NUMSTAT |
				      DIFF_FORMAT_DIFFSTAT |
				      DIFF_FORMAT_SHORTSTAT |
				      DIFF_FORMAT_SUMMARY |
				      DIFF_FORMAT_CHECKDIFF))
		options->recursive = 1;


	if (options->pickaxe)
		options->recursive = 1;

	if (options->detect_rename && options->rename_limit < 0)
		options->rename_limit = diff_rename_limit_default;
	if (options->setup & DIFF_SETUP_USE_CACHE) {
		if (!active_cache)


			read_cache();
	}
	if (options->abbrev <= 0 || 40 < options->abbrev)
		options->abbrev = 40;


	if (options->quiet) {
		options->output_format = DIFF_FORMAT_NO_OUTPUT;
		options->exit_with_status = 1;
	}


	if (options->pickaxe || options->filter)
		options->quiet = 0;

	return 0;
}
