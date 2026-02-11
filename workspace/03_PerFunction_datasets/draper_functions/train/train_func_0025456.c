main(int argc, char **argv)
{
	char *temp, *s;

	commands = (CommandChain*)safemalloc(sizeof(CommandChain));
	commands->first = commands->last = NULL;


	temp = argv[0];
	s = strrchr(argv[0], '/');
	if (s != NULL)
	{
		temp = s + 1;
	}

	Module = temp;
	configPrefix = CatString2("*", Module);

	if ((argc != 6) && (argc != 7))
	{
		fprintf(stderr,
			"%s Version %s should only be executed by fvwm!\n",
			Module, VERSION);
		exit(1);
	}

	fvwm_fd[0] = atoi(argv[1]);
	fvwm_fd[1] = atoi(argv[2]);


	dpy = XOpenDisplay(displayName);
	if (!dpy)
	{
		fprintf(stderr, "%s:  unable to open display '%s'\n",
			Module, XDisplayName (displayName));
		exit (2);
	}
	screen = DefaultScreen(dpy);
	root = RootWindow(dpy, screen);
	MyDisplayHeight = DisplayHeight(dpy, screen);
	MyDisplayWidth = DisplayWidth(dpy, screen);
	XSetErrorHandler(ErrorHandler);
	flib_init_graphics(dpy);

	XA_XSETROOT_ID = XInternAtom(dpy, "_XSETROOT_ID", False);
	XA_ESETROOT_PMAP_ID = XInternAtom(dpy, "ESETROOT_PMAP_ID", False);
	XA_XROOTPMAP_ID = XInternAtom(dpy, "_XROOTPMAP_ID", False);

	signal (SIGPIPE, DeadPipe);


	ParseConfig();

	SetMessageMask(fvwm_fd,
		       M_NEW_PAGE | M_NEW_DESK | M_CONFIG_INFO |
		       M_END_CONFIG_INFO | M_SENDCONFIG);


	SendInfo(fvwm_fd, "Send_WindowList", 0);


	SendFinishedStartupNotification(fvwm_fd);


	EndLessLoop();


	return 1;
}
