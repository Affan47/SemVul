check_configuration(int dump)
{
	struct hub_config configuration;
	int ret = read_config(arg_config, &configuration, 0);

	if (dump)
	{
		if (ret != -1)
		{
			dump_config(&configuration, dump > 1);
		}
		return 0;
	}

	if (ret == -1)
	{
		fprintf(stderr, "ERROR\n");
        	return 1;
	}

	fprintf(stdout, "OK\n");
	return 0;
}
