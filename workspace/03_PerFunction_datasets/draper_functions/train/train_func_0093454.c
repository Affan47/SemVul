parse_delay_arg (const char *optarg,  pf_conf_t *conf)
{
	struct {
		const char *name;
		uint *value;
	} table[] = {
		{ "start",	&conf->start_delay_sec },
		{ "close",	&conf->close_delay_sec },
		{ NULL,		NULL }
	}, *p;

	for (p=table; p->name; p++) {
		uint nlen = strlen (p->name);
		if (strncmp (p->name, optarg, nlen)
				|| optarg[nlen] != '=')
			continue;

		*(p->value) = atoi(optarg+nlen+1);
		return;
	}

	fprintf (stderr, "Delay format: -d <what>=<delay>\n"
			"Valid for <what>: ");
	for (p=table; p->name; p++)
		fprintf (stderr, "%s ", p->name);
	fprintf (stderr, "\n");
	exit(EXIT_FAILURE);
}
