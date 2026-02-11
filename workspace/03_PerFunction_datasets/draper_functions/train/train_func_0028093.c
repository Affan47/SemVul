check_pid(char *pid_file)
{
	struct stat stb;
	FILE *pidfile;

	if (stat(pid_file, &stb) == 0)
	{
		pidfile = fopen(pid_file, "r");
		if (pidfile)
		{
			char buf[64];
			pid_t pid = 0;
			memset(buf, 0, sizeof(buf));
			if (fread(buf, 1, sizeof(buf), pidfile))
			{
				buf[sizeof(buf) - 1] = '\0';
				pid = atoi(buf);
			}
			fclose(pidfile);
			if (pid && kill(pid, 0) == 0)
			{
				return TRUE;
			}
		}
		DBG1(DBG_APP, "removing pidfile '%s', process not running", pid_file);
		unlink(pid_file);
	}
	return FALSE;
}
