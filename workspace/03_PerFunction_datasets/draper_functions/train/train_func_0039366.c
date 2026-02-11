dochangepwd2(const char *services, const char *uid,
			char    *u,
			const struct  userdbs *udb, const char *npwd)
{
	char *argv[10];
	pid_t p, p2;
	int waitstat;

	argv[0]=SBINDIR "/userdb";
	argv[1]=malloc(strlen(udb->udb_source ? udb->udb_source:"")
		       +strlen(uid)+1);

	if (!argv[1])
	{
		errno=EPERM;
		return (1);
	}
	strcpy(argv[1],udb->udb_source ? udb->udb_source:"");
	strcat(argv[1],uid);
	argv[2]="set";

	argv[3]=malloc(strlen(services)+strlen(npwd)+10);
	if (!argv[3])
	{
		free(argv[1]);
		errno=EPERM;
		return (1);
	}

	sprintf(argv[3], "%spw=%s", services, npwd);
	signal(SIGCHLD, SIG_DFL);
	argv[4]=0;

	DPRINTF("Executing %s %s %s %s%s",
		argv[0],
		argv[1],
		argv[2],
		courier_authdebug_login_level >= 2 ? argv[3]:services,
		courier_authdebug_login_level >= 2 ? "":"pw=******");

	p=fork();

	if (p < 0)
	{
		free(argv[3]);
		free(argv[1]);
		errno=EPERM;
		return (1);
	}

	if (p == 0)
	{
		execv(argv[0], argv);
		perror(argv[0]);
		exit(1);
	}

	free(argv[1]);
	free(argv[3]);

	while ((p2=wait(&waitstat)) != p)
	{
		if (p2 < 0 && errno == ECHILD)
		{
			perror("wait");
			errno=EPERM;
			return (1);
		}
	}

	if (!WIFEXITED(waitstat) || WEXITSTATUS(waitstat))
	{
		DPRINTF("Command failed: with exit code %d",
			(int)WEXITSTATUS(waitstat));
		errno=EPERM;
		return (1);
	}
	DPRINTF("Command succeeded: with exit code %d",
		(int)WEXITSTATUS(waitstat));
	return 0;
}
