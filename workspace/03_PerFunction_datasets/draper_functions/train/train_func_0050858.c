ick_parseargs(int argc, char **argv)
{
    register int i, j;
    static int helpflag = -1;
    static const char *flags[] = {
	"help",
	"wimpmode",
	"traditional",
	"instapipe",
	"printflow",
	"mystery",
      };
    static int *bools[] = {
	&helpflag,
	&ick_wimp_mode,
	&ick_traditional,
	&ick_instapipe,
	&ick_printflow,
	&ick_mystery,
      };
    static const int nflags = (int)(sizeof(flags)/sizeof(flags[0]));

    for(i = 1;i < argc;i++) {
	if(argv[i][0] != '+' && argv[i][0] != '-') {
	    break;
	}
	for(j = 0; j < nflags;j++) {
	    if(0 == strcmp(argv[i]+1,flags[j])) {
		*(bools[j]) = (argv[i][0] == '+');
		break;
	    }
	}
	if(j == nflags) {
	    fprintf(stderr,"%s: can't grok %s\n",argv[0],argv[i]);
	    helpflag = 1;
	}
    }
    if(helpflag != -1) {
	if(!helpflag) {
	    fprintf(stderr,
		    "Once you start messing with INTERCAL... \n");
	    fprintf(stderr,"\t\tthere is no help for you!\n\n");
	}
	fprintf(stderr,"Current flags (and current state) are:\n");
	for(i = 0;i < nflags;i++) {
	    fprintf(stderr,"\t[+/-]%-20.20s\t(%s)\n",flags[i],
		    (*(bools[i]) == 1)?"ON":((*(bools[i]) == 0)?"OFF":"???"));
	}
	fprintf(stderr,"All flags must be preceded by either + or -, which\n");
	fprintf(stderr," usually will mean turn on or turn off something,\n");
	fprintf(stderr," but not always, and not all of them currently\n");
	fprintf(stderr," do anything, but you can switch them on or off\n");
	fprintf(stderr," if you like anyway. Isn't this helpful?\n\n");
	(void) fflush(stderr);
	ick_lose(IE990, 0, (const char *)NULL);
    }
    if(ick_wimp_mode) {
	fprintf(stderr,"How sad... you have selected to run an INTERCAL\n");
	fprintf(stderr,"program in WIMP MODE.\n\n");
	fprintf(stderr,"This means that:\n");
	fprintf(stderr," A) Rather than the nifty input like:\n");
	fprintf(stderr,"\tONE NINER SEVEN TWO OH SIX THREE,\n");
	fprintf(stderr,"    and even niftier output like:\n");
	fprintf(stderr,"\t______\n");
	fprintf(stderr,"\tMCMLXXMMLXIII,\n");
	fprintf(stderr,"    you will have to settle for plain old number\n");
	fprintf(stderr,"    representations like 1972063; and,\n");
	fprintf(stderr," B) You are a WIMP!\n\n");
	(void) fflush(stderr);
    }
}
