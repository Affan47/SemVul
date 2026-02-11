rc_conf_srv(char *optname)
{
	OPTION *option;

	option = find_option(optname, OT_SRV);

	if (option == NULL)
		fatal("rc_conf_srv: unkown config option requested: %s", optname);
	return (SERVER *)option->val;
}
