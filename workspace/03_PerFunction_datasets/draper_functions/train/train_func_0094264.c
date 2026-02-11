upsclient_update_vars(void)
{
	int		ret;
	unsigned int	numq, numa;
	const char	*query[4];
	char		**answer;

	query[0] = "VAR";
	query[1] = client_upsname;
	numq = 2;

	ret = upscli_list_start(ups, numq, query);

	if (ret < 0)
	{
		upsdebugx(1, "Error: %s (%i)", upscli_strerror(ups), upscli_upserror(ups));
		return ret;
	}

	while (upscli_list_next(ups, numq, query, &numa, &answer) == 1)
	{

		if (numa < 4)
		{
			upsdebugx(1, "Error: insufficient data (got %d args, need at least 4)", numa);
		}

		upsdebugx(5, "Received: %s %s %s %s",
				answer[0], answer[1], answer[2], answer[3]);


		if (strncmp(answer[2], "driver.", 7))
			setvar(answer[2], answer[3]);
	}
	return 1;
}
