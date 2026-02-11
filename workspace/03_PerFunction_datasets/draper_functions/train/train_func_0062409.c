cmd_xit(frommark, tomark, cmd, bang, extra)
	MARK	frommark, tomark;
	CMD	cmd;
	int	bang;
	char	*extra;
{
	static long	whenwarned;
	int		oldflag;


	if (argno + 1 < nargs && whenwarned != changes && (!bang || cmd != CMD_QUIT))
	{
		msg("More files to edit -- Use \":n\" to go to next file");
		whenwarned = changes;
		return;
	}

	if (cmd == CMD_QUIT)
	{
		if (tmpabort(bang))
		{
			mode = MODE_QUIT;
		}
		else
		{
			msg("Use q! to abort changes, or wq to save changes");
		}
	}
	else
	{

		oldflag = tstflag(file, MODIFIED);
		if (cmd == CMD_WQUIT)
			setflag(file, MODIFIED);
		if (tmpend(bang))
		{
			mode = MODE_QUIT;
		}
		else
		{
			msg("Could not save file -- use quit! to abort changes, or w filename");
		}
		if (!oldflag)
			clrflag(file, MODIFIED);
	}
}
