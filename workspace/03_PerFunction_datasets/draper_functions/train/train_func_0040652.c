load_config(void)
{
	const char *opt;

	opt = conf_get_opt("ppp", "ccp");
	if (opt && atoi(opt) >= 0)
		conf_ccp = atoi(opt);

	opt = conf_get_opt("ppp", "ccp-max-configure");
	if (opt && atoi(opt) > 0)
		conf_ccp_max_configure = atoi(opt);
}
