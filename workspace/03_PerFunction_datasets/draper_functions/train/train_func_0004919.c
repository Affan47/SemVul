main(int argc, char **argv)
{
	char	*pdir;
#if	defined(NHONSUID) || defined(DEBUG)
	int_ugid_t	chk_uid;
#endif
	versionprint(argv, "$Revision: 1.1 $", 0);

	if  ((progname = strrchr(argv[0], '/')))
		progname++;
	else
		progname = argv[0];

	init_mcfile();

	Realuid = getuid();
	Effuid = geteuid();
	INIT_DAEMUID;
	Cfile = open_cfile(MISC_UCONFIG, "rest.help");
	SCRAMBLID_CHECK
	SWAP_TO(Daemuid);
	mypriv = getspuser(Realuid);
	Displayopts.opt_classcode = mypriv->spu_class;

	setuid(Daemuid);

	if  (argc < 2)  {
	usage:
		fprintf(stderr, "Usage: %s [-n] ptr [form]\n", progname);
		exit(E_USAGE);
	}
	if  (strcmp(argv[1], "-n") == 0)  {
		expandem = 0;
		argv++;
		argc--;
	}

	if  (argc < 2  ||  argc > 3)
		goto  usage;

	if  ((Ctrl_chan = msgget(MSGID, 0)) < 0)  {
		fprintf(stderr, "%s: Spooler not running\n", progname);
		exit(E_NOTRUN);
	}

#ifndef	USING_FLOCK


	if  ((Sem_chan = semget(SEMID, SEMNUMS, IPC_MODE)) < 0)  {
		fprintf(stderr, "%s: Cannot open semaphore\n", progname);
		exit(E_SETUP);
	}
#endif

	if  (!jobshminit(0))  {
		fprintf(stderr, "%s: Cannot open jshm\n", progname);
		return  E_JOBQ;
	}
	if  (!ptrshminit(0))  {
		fprintf(stderr, "%s: Cannot open pshm\n", progname);
		return  E_PRINQ;
	}
	readptrlist(1);
	pdir = envprocess(PTDIR);
	if  (chdir(pdir) < 0)  {
		fprintf(stderr, "%s: Cannot open ptr dir %s\n", progname, pdir);
		exit(E_SETUP);
	}

	return  do_bizniz(argv[1], argv[2]);
}
