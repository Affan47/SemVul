cmd_varnishtest(CMD_ARGS)
{

	(void)priv;
	(void)cmd;
	(void)vl;

	if (av == NULL)
		return;
	assert(!strcmp(av[0], "varnishtest"));

	vtc_log(vl, 1, "TEST %s", av[1]);
	AZ(av[2]);
	vtc_desc = strdup(av[1]);
}
