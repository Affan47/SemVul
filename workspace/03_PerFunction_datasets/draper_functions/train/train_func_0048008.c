git_diff_basic_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "diff.renamelimit")) {
		diff_rename_limit_default = git_config_int(var, value);
		return 0;
	}

	switch (userdiff_config(var, value)) {
		case 0: break;
		case -1: return -1;
		default: return 0;
	}

	if (!prefixcmp(var, "diff.color.") || !prefixcmp(var, "color.diff.")) {
		int slot = parse_diff_color_slot(var, 11);
		if (slot < 0)
			return 0;
		if (!value)
			return config_error_nonbool(var);
		color_parse(value, var, diff_colors[slot]);
		return 0;
	}


	if (!strcmp(var, "diff.suppressblankempty") ||

			!strcmp(var, "diff.suppress-blank-empty")) {
		diff_suppress_blank_empty = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "diff.dirstat")) {
		struct strbuf errmsg = STRBUF_INIT;
		default_diff_options.dirstat_permille = diff_dirstat_permille_default;
		if (parse_dirstat_params(&default_diff_options, value, &errmsg))
			warning(_("Found errors in 'diff.dirstat' config variable:\n%s"),
				errmsg.buf);
		strbuf_release(&errmsg);
		diff_dirstat_permille_default = default_diff_options.dirstat_permille;
		return 0;
	}

	if (!prefixcmp(var, "submodule."))
		return parse_submodule_config_option(var, value);

	return git_color_default_config(var, value, cb);
}
