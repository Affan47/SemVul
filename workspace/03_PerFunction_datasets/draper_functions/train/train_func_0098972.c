env_options()
{
    char *argv[MAXARGV];
    char *envopts;
    int argc;

    envopts = getenv("EXIFPROBE_OPTIONS");
    if(envopts && *envopts)
    {
        optind = 0;

        argc = vector(envopts,argv," \t",0,MAXARGV);
        (void)process_options(argc,argv);
        optind = 1;
    }
}
