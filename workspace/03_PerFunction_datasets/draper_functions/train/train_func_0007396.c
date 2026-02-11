git_status_config(const char *k, const char *v)
{
	if (!strcmp(k, "status.submodulesummary")) {
		int is_bool;
		wt_status_submodule_summary = git_config_bool_or_int(k, v, &is_bool);
		if (is_bool && wt_status_submodule_summary)
			wt_status_submodule_summary = -1;
		return 0;
	}
	if (!strcmp(k, "status.color") || !strcmp(k, "color.status")) {
		wt_status_use_color = git_config_colorbool(k, v, -1);
		return 0;
	}
	if (!prefixcmp(k, "status.color.") || !prefixcmp(k, "color.status.")) {
		int slot = parse_status_slot(k, 13);
		if (!v)
			return config_error_nonbool(k);
		color_parse(v, k, wt_status_colors[slot]);
		return 0;
	}
	if (!strcmp(k, "status.relativepaths")) {
		wt_status_relative_paths = git_config_bool(k, v);
		return 0;
	}
	return git_color_default_config(k, v);
}
