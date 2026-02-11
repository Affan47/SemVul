main(int argc, char **argv)
{
    DCM_OBJECT *obj1;
    CONDITION cond;
    CTNBOOLEAN
	verbose = FALSE,
	exitFlag = FALSE;
    unsigned long
        options = DCM_ORDERLITTLEENDIAN;
    long vmLimit = 0;
    long differences = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
	switch (*(argv[0] + 1)) {
	case 'm':
	    argc--;
	    argv++;
	    vmLimit = atoi(*argv);
	    break;
	case 't':
	    options &= ~DCM_FILEFORMATMASK;
	    options |= DCM_PART10FILE;
	    break;
	case 'v':
	    verbose = TRUE;
	    break;
	case 'z':
	    options |= DCM_FORMATCONVERSION;
	    break;
	default:
	    break;
	}
    }

    THR_Init();
    DCM_Debug(verbose);
    if (argc != 1)
	usageerror();

    cond = DCM_OpenFile(*argv, options, &obj1);
    if (cond != DCM_NORMAL && ((options & DCM_PART10FILE) == 0)) {
	COND_DumpConditions();
	(void) DCM_CloseObject(&obj1);
	(void) COND_PopCondition(TRUE);
	cond = DCM_OpenFile(*argv, options | DCM_PART10FILE, &obj1);
    }
    if (cond != DCM_NORMAL) {
	COND_DumpConditions();
	THR_Shutdown();
	exit(1);
    }

    printf("<HTML>\n");
    printf("<HEAD>\n");
    printf("<META HTTP-EQUIV=""Content-Type"" CONTENT=""text/html; charset=iso-2022-jp"">\n");
    printf("<TITLE>dcm_to_html</TITLE>\n");
    printf("</HEAD>");

    printf("<BODY BGCOLOR=#ffffff FGCOLOR=#ff000000>\n");
    printf("<TABLE BORDER>\n");
    DCM_ScanParseObject(&obj1,
			NULL, 0,
			NULL, 0,
			callback, NULL);
    printf("</TABLE>\n");
    printf("</BODY>\n");
    printf("</HTML>");

    (void) DCM_CloseObject(&obj1);;

#ifdef MALLOC_DEBUG
    malloc_verify(0);
    malloc_shutdown();
#endif
    THR_Shutdown();
    return 0;
}
