loadHugs(argc,argv)
int    argc;
char* argv[]; {
    hugs = initHugsServer(argc,argv);
    if (NULL == hugs) {
	fprintf(stderr,"runhugs: Unable to initialise Hugs (%s)\n", lastError);
	fflush(stderr);
	exit(1);
    }
    hugs->setOutputEnable(0);
    check();
}
