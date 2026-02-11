nextfile(prev)
bool prev;
{
    char *name = NULL;
    int newpc=pc,
	myargc=0;
    char **myargv;
    bool newlist = NO;

    if (prev == 0)
	while ( (name=getarg()) )
	    if (!expandargs(name, &myargc, &myargv))
		return;

    if (oktoedit(autowrite)) {
	if (prev || (myargc == 1 && strcmp(myargv[0],"-") == 0)) {
	    if (pc > 0) {
		newpc = pc-1;
	    }
	    else {
		prints("(no prev files)");
		goto killem;
	    }
	}
	else if (myargc == 0) {
	    if (pc < argc-1) {
		newpc = 1+pc;
	    }
	    else {
		prints("(no more files)");
		goto killem;
	    }
	}
	else if (myargc > 1 || (newpc = findarg(myargv[0])) < 0) {
	    toedit(myargc);
	    newpc = 0;
	    newlist++;
	}
	doinput(newlist ? myargv[0] : argv[newpc]);
	pc = newpc;
	if (newlist) {
	    killargs(&argc, &argv);
	    argc = myargc;
	    argv = myargv;
	}
	else
    killem: if (!prev)
		killargs(&myargc, &myargv);
    }
}
