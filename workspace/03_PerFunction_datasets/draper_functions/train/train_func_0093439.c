start_driver(const ups_t *ups)
{
	char	*argv[8];
	char	dfn[SMALLBUF];
	int	ret, arg = 0;
	struct stat	fs;

	upsdebugx(1, "Starting UPS: %s", ups->upsname);

	snprintf(dfn, sizeof(dfn), "%s/%s", driverpath, ups->driver);
	ret = stat(dfn, &fs);

	if (ret < 0)
		fatal_with_errno(EXIT_FAILURE, "Can't start %s", dfn);

	argv[arg++] = dfn;
	argv[arg++] = (char *)"-a";
	argv[arg++] = ups->upsname;


	if (pt_root) {
		argv[arg++] = (char *)"-r";
		argv[arg++] = pt_root;
	}

	if (pt_user) {
		argv[arg++] = (char *)"-u";
		argv[arg++] = pt_user;
	}


	argv[arg++] = NULL;

	debugcmdline(2, "exec: ", argv);

	if (!testmode) {
		forkexec(argv, ups);
	}
}
