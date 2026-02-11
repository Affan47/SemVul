_PyOS_GetOpt(int argc, wchar_t **argv, wchar_t *optstring)
{
    wchar_t *ptr;
    wchar_t option;

    if (*opt_ptr == '\0') {

        if (_PyOS_optind >= argc)
            return -1;
#ifdef MS_WINDOWS
        else if (wcscmp(argv[_PyOS_optind], L"/?") == 0) {
            ++_PyOS_optind;
            return 'h';
        }
#endif

        else if (argv[_PyOS_optind][0] != L'-' ||
                 argv[_PyOS_optind][1] == L'\0'  )
            return -1;

        else if (wcscmp(argv[_PyOS_optind], L"--") == 0) {
            ++_PyOS_optind;
            return -1;
        }

        else if (wcscmp(argv[_PyOS_optind], L"--help") == 0) {
            ++_PyOS_optind;
            return 'h';
        }

        else if (wcscmp(argv[_PyOS_optind], L"--version") == 0) {
            ++_PyOS_optind;
            return 'V';
        }


        opt_ptr = &argv[_PyOS_optind++][1];
    }

    if ( (option = *opt_ptr++) == L'\0')
        return -1;

    if (option == 'J') {
        fprintf(stderr, "-J is reserved for Jython\n");
        return '_';
    }

    if ((ptr = wcschr(optstring, option)) == NULL) {
        if (_PyOS_opterr)
          fprintf(stderr, "Unknown option: -%c\n", (char)option);

        return '_';
    }

    if (*(ptr + 1) == L':') {
        if (*opt_ptr != L'\0') {
            _PyOS_optarg  = opt_ptr;
            opt_ptr = L"";
        }

        else {
            if (_PyOS_optind >= argc) {
                if (_PyOS_opterr)
                    fprintf(stderr,
                        "Argument expected for the -%c option\n", (char)option);
                return '_';
            }

            _PyOS_optarg = argv[_PyOS_optind++];
        }
    }

    return option;
}
