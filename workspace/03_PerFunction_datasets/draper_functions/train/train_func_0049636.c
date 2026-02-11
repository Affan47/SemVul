args_ok(int argc, char *argv[])
{
    struct arglist *hscdepp_args;
    BOOL arg_help = FALSE;
    BOOL arg_license = FALSE;
    BOOL ok = FALSE;


    hscdepp_args = prepare_args
        ("HSCDEPP_ARGS",
         "FILE/T", &makefile, "makefile to update",
         "PRJFILE/T/K", &prjfile, "project file",
         "NAMEALL/T/K", &nameall, "name for `all_hsc' rule",
         "VERBOSE/S", &verbose, "verbose output",
         "NOBACKUP/S", &nobackup, "do not backup makefile",
         "NOTAGLINES/S", &notaglines, "do not write taglines",
         "-DEBUG/S", &debug, "enable debugging output",
         "HELP=?=-h=--help/S", &arg_help, "display this text",
         "LICENSE/S", &arg_license, "display license",
         NULL);

    ok = (hscdepp_args != NULL);


    if (ok)
    {
        ok = set_args(argc, argv, hscdepp_args);


        if (!ok)
        {
            pargerr();
            set_return_code(RC_ERROR);
        }
        else if (arg_help || arg_license)
        {


            fprintf_prginfo(stderr);
            if (arg_help)
                fprintf_arghelp(stderr, hscdepp_args);
            else
                show_license();
            set_return_code(RC_WARN);
            ok = FALSE;
        }
        else
        {

            if (debug)
                verbose = TRUE;


            if (verbose)
                fprintf_prginfo(stderr);


            if (!prjfile)
            {
                prjfile = DEFAULT_PROJECT;
                if (verbose)
                    fprintf(stderr, HD "%s: using default project-file\n",
                            prjfile);
            }
            if (!nameall)
            {
                nameall = DEFAULT_NAMEALL;

            }


            D(
                 if (makefile)
                 {
                 fprintf(stderr, DHD "makefile=`%s'\n", makefile);
                 fprintf(stderr, DHD "makefile=DEFAULT\n");
                 fprintf(stderr, DHD "prjfile =`%s'\n", prjfile);
                 fprintf(stderr, DHD "nameall =`%s'\n", nameall);
                 }
            );
        }


        free_args(hscdepp_args);
    }
    else
    {

        D(fprintf(stderr, SHIT "ArgDef error: %lu\n", prep_error_num));
    }

#if 1
    return (ok);
#else
    return (FALSE);
#endif
}
