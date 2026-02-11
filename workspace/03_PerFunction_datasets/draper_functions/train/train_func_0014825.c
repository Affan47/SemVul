cli_count_filter_init(struct cli_def *cli, int argc, char **argv, struct cli_filter *filt)
{
	if (argc > 1)
	{
		if (cli->client)
			fprintf(cli->client, "Count filter does not take arguments%s", cli->newline);

		return CLI_ERROR;
	}

	filt->filter = cli_count_filter;
	filt->data = calloc(sizeof(int), 1);

	return CLI_OK;
}
