run(int argc, char** argv)
{
    extern int optind;
    extern char* optarg;
    int c;

    resetConfig();
    readConfig(FAX_SYSCONF);
    readConfig(FAX_USERCONF);

    bool jobs = true;
    bool docs = false;
    bool useadmin = false;

    while ((c = Sys::getopt(argc, argv, "ah:dv")) != -1)
	switch (c) {
	case 'a':
	    useadmin = true;
	    break;
	case 'd':
	    jobs = false;
	    docs = true;
	    break;
	case 'h':
	    setHost(optarg);
	    break;
	case 'v':
	    setVerbose(true);
	    break;
	case '?':
	    usage();
	}
    if (optind >= argc)
	usage();
    fxStr emsg;
    if (callServer(emsg)) {
	if (login(NULL, emsg) &&
	    (!useadmin || admin (NULL, emsg))) {

	    for (; optind < argc; optind++) {
		const char* id = argv[optind];
		if (jobs) {
		    if (!removeJob(id, emsg))
			break;
		} else if (docs) {
		    if (!deleteDoc(id)) {
			emsg = getLastResponse();
			break;
		    }

		    printf(_("%s removed.\n"), id);
		}
	    }
	}
	hangupServer();
    }
    if (emsg != "")
	printError("%s", (const char*) emsg);
}
