cfg_get_log_target(gn_log_target *t, const char *opt)
{
	char *val;

	if (!(val = gn_cfg_get(gn_cfg_info, "logging", opt)))
		val = "off";

	if (!strcasecmp(val, "off"))
		*t = GN_LOG_T_NONE;
	else if (!strcasecmp(val, "on"))
		*t = GN_LOG_T_STDERR;
	else {
		fprintf(stderr, _("Unsupported [%s] %s value \"%s\"\n"), "logging", opt, val);
		fprintf(stderr, _("Use either \"%s\" or \"%s\".\n"), "off", "on");
		fprintf(stderr, _("Assuming: %s\n"), "off");
		*t = GN_LOG_T_NONE;
	}

	return true;
}
