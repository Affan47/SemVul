diff_setup(struct diff_options *options)
{
	memcpy(options, &default_diff_options, sizeof(*options));

	options->file = stdout;

	options->line_termination = '\n';
	options->break_opt = -1;
	options->rename_limit = -1;
	options->dirstat_permille = diff_dirstat_permille_default;
	options->context = 3;

	options->change = diff_change;
	options->add_remove = diff_addremove;
	if (diff_use_color_default > 0)
		DIFF_OPT_SET(options, COLOR_DIFF);
	options->detect_rename = diff_detect_rename_default;

	if (diff_no_prefix) {
		options->a_prefix = options->b_prefix = "";
	} else if (!diff_mnemonic_prefix) {
		options->a_prefix = "a/";
		options->b_prefix = "b/";
	}
}
