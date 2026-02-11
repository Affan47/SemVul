SetWALFileNameForCleanup(void)
{
	bool		fnameOK = false;

	TrimExtension(restartWALFileName, additional_ext);


	if (IsXLogFileName(restartWALFileName))
	{
		strcpy(exclusiveCleanupFileName, restartWALFileName);
		fnameOK = true;
	}
	else if (IsPartialXLogFileName(restartWALFileName))
	{
		int			args;
		uint32		tli = 1,
					log = 0,
					seg = 0;

		args = sscanf(restartWALFileName, "%08X%08X%08X.partial",
					  &tli, &log, &seg);
		if (args == 3)
		{
			fnameOK = true;


			XLogFileNameById(exclusiveCleanupFileName, tli, log, seg);
		}
	}
	else if (IsBackupHistoryFileName(restartWALFileName))
	{
		int			args;
		uint32		tli = 1,
					log = 0,
					seg = 0,
					offset = 0;

		args = sscanf(restartWALFileName, "%08X%08X%08X.%08X.backup", &tli, &log, &seg, &offset);
		if (args == 4)
		{
			fnameOK = true;


			XLogFileNameById(exclusiveCleanupFileName, tli, log, seg);
		}
	}

	if (!fnameOK)
	{
		fprintf(stderr, "%s: invalid filename input\n", progname);
		fprintf(stderr, "Try \"%s --help\" for more information.\n", progname);
		exit(2);
	}
}
