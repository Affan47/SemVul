stf_parse_options_new (void)
{
	StfParseOptions_t* parseoptions = g_new0 (StfParseOptions_t, 1);

	parseoptions->parsetype   = PARSE_TYPE_NOTSET;

	parseoptions->terminator  = NULL;
	stf_parse_options_add_line_terminator (parseoptions, "\r\n");
	stf_parse_options_add_line_terminator (parseoptions, "\n");
	stf_parse_options_add_line_terminator (parseoptions, "\r");

	parseoptions->trim_spaces = (TRIM_TYPE_RIGHT | TRIM_TYPE_LEFT);
	parseoptions->locale = NULL;

	parseoptions->splitpositions = NULL;
	stf_parse_options_fixed_splitpositions_clear (parseoptions);

	parseoptions->stringindicator = '"';
	parseoptions->indicator_2x_is_single = TRUE;
	parseoptions->sep.duplicates = FALSE;
	parseoptions->trim_seps = FALSE;

	parseoptions->sep.str = NULL;
	parseoptions->sep.chr = NULL;

	parseoptions->col_autofit_array = NULL;
	parseoptions->col_import_array = NULL;
	parseoptions->col_import_array_len = 0;
	parseoptions->formats = NULL;

	parseoptions->cols_exceeded = FALSE;
	parseoptions->rows_exceeded = FALSE;
	parseoptions->ref_count = 1;

	return parseoptions;
}
