fish_parse_opt(int argc, char **argv, std::vector<std::string> *out_cmds)
{
    int my_optind;
    int force_interactive=0;
    bool has_cmd = false;

    while (1)
    {
        static struct option
                long_options[] =
        {
            { "command", required_argument, 0, 'c' },
            { "debug-level", required_argument, 0, 'd' },
            { "interactive", no_argument, 0, 'i' } ,
            { "login", no_argument, 0, 'l' },
            { "no-execute", no_argument, 0, 'n' },
            { "profile", required_argument, 0, 'p' },
            { "help", no_argument, 0, 'h' },
            { "version", no_argument, 0, 'v' },
            { 0, 0, 0, 0 }
        }
        ;

        int opt_index = 0;

        int opt = getopt_long(argc,
                              argv,
                              GETOPT_STRING,
                              long_options,
                              &opt_index);

        if (opt == -1)
            break;

        switch (opt)
        {
            case 0:
            {
                break;
            }

            case 'c':
            {
                out_cmds->push_back(optarg ? optarg : "");
                has_cmd = true;
                is_interactive_session = 0;
                break;
            }

            case 'd':
            {
                char *end;
                long tmp;

                errno = 0;
                tmp = strtol(optarg, &end, 10);

                if (tmp >= 0 && tmp <=10 && !*end && !errno)
                {
                    debug_level = (int)tmp;
                }
                else
                {
                    debug(0, _(L"Invalid value '%s' for debug level switch"), optarg);
                    exit_without_destructors(1);
                }
                break;
            }

            case 'h':
            {
                out_cmds->push_back("__fish_print_help fish");
                has_cmd = true;
                break;
            }

            case 'i':
            {
                force_interactive = 1;
                break;
            }

            case 'l':
            {
                is_login=1;
                break;
            }

            case 'n':
            {
                no_exec=1;
                break;
            }

            case 'p':
            {
                profile = optarg;
                break;
            }

            case 'v':
            {
                fwprintf(stderr,
                         _(L"%s, version %s\n"),
                         PACKAGE_NAME,
                         PACKAGE_VERSION);
                exit_without_destructors(0);
            }

            case '?':
            {
                exit_without_destructors(1);
            }

        }
    }

    my_optind = optind;

    is_login |= (strcmp(argv[0], "-fish") == 0);


    is_interactive_session &= ! has_cmd;
    is_interactive_session &= (my_optind == argc);
    is_interactive_session &= isatty(STDIN_FILENO);


    is_interactive_session |= force_interactive;

    return my_optind;
}
