T0CmdParsing(unsigned char *cmd, unsigned int cmd_len,
	 unsigned int *exp_len)
{
	*exp_len = 0;


	switch (cmd_len)
	{
		case 4:
			*exp_len = 2;
			break;

		case 5:
			if (cmd[4] != 0)
				*exp_len = cmd[4] + 2;
			else
				*exp_len = 256 + 2;
			break;

		default:
			if (cmd_len > 5 && cmd_len == (unsigned int)(cmd[4] + 5))
				*exp_len = 2;
			else
				return IFD_COMMUNICATION_ERROR;
			break;
	}

	return IFD_SUCCESS;
}
