reopen_config_file(void)
{
	free(default_local_hostname);
	default_local_hostname = xstrdup("*");
	if (parser != NULL)
		config_close(parser);
	parser = config_open(config_filename);
	return (parser != NULL);
}
