glk_main(void)
#else
int main(int argc, char *argv[])
#endif
{
#ifdef DMALLOC


#endif


    setlocale(LC_ALL, "");


    lin = col = 1;
    header->pageLength = 24;
    header->pageWidth = 70;

    getPageSize();

#ifdef HAVE_GLK

#else
    args(argc, argv);

    if (adventureFileName == NULL || strcmp(adventureFileName, "") == 0) {
	printf("You should supply a game file to play.\n");
	usage(PROGNAME);
	terminate(0);
    }
#endif

    if ((debugOption && !regressionTestOption) || verboseOption) {
	if (debugOption) printf("<");
	printVersion(BUILD);
	if (debugOption) printf(">");
	newline();
	newline();
    }

#ifdef HAVE_GARGLK
    garglk_set_story_name(adventureName);
#endif

    run();

#ifdef HAVE_GLK
    return;
#else
    return(EXIT_SUCCESS);
#endif
}
