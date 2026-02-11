_read_mirror_params(struct lvcreate_params *lp,
			       struct cmd_context *cmd)
{
	int region_size;
	const char *mirrorlog;
	int corelog = arg_count(cmd, corelog_ARG);

	mirrorlog = arg_str_value(cmd, mirrorlog_ARG,
				  corelog ? "core" : DEFAULT_MIRRORLOG);

	if (strcmp("core", mirrorlog) && corelog) {
		log_error("Please use only one of --mirrorlog or --corelog");
		return 0;
	}

	if (!strcmp("mirrored", mirrorlog)) {
		lp->log_count = 2;
	} else if (!strcmp("disk", mirrorlog)) {
		lp->log_count = 1;
	} else if (!strcmp("core", mirrorlog))
		lp->log_count = 0;
	else {
		log_error("Unknown mirrorlog type: %s", mirrorlog);
		return 0;
	}

	log_verbose("Setting logging type to %s", mirrorlog);

	lp->nosync = arg_is_set(cmd, nosync_ARG);

	if (arg_count(cmd, regionsize_ARG)) {
		if (arg_sign_value(cmd, regionsize_ARG, SIGN_NONE) == SIGN_MINUS) {
			log_error("Negative regionsize is invalid");
			return 0;
		}
		lp->region_size = arg_uint_value(cmd, regionsize_ARG, 0);
	} else {
		region_size = 2 * find_config_tree_int(cmd,
					"activation/mirror_region_size",
					DEFAULT_MIRROR_REGION_SIZE);
		if (region_size < 0) {
			log_error("Negative regionsize in configuration file "
				  "is invalid");
			return 0;
		}
		lp->region_size = region_size;
	}

	if (!_validate_mirror_params(cmd, lp))
		return 0;

	return 1;
}
