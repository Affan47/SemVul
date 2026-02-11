set_positional_option(arg)
     char *arg;
{
    int copies;
    int lines;
    float size;

    switch (arg[1]) {
        case NUL:
            break;
        case '#':
            if (sscanf(&arg[2], "%d", &copies) != 1 || copies <= 0)
                fprintf(stderr, "Bad number of copies: '%s'. Ignored\n", &arg[2]);
            else
                copies_number = copies;
            printf("/#copies %d def\n", copies_number);
            break;
        case '1':
            if (arg[2] != NUL)
                usage(EXIT_FAILURE);
            new_twinpages = FALSE;
            break;
        case '2':
            if (arg[2] != NUL)
                usage(EXIT_FAILURE);
            new_twinpages = TRUE;
            break;
        case 'B':
            new_fontweight = BOLD;
            break;
        case 'd':
            printdate = TRUE;
            break;
        case 'F':
            if (arg[2] == NUL || sscanf(&arg[2], "%f", &size) != 1 || size == 0.0) {
                fprintf(stderr, "Wrong value for option -F: '%s'. Ignored\n",
                        &arg[2]);
                break;
            }
            new_fontsize = size;
            break;
        case 'H':
            header_text = arg+2;
            break;
        case 'l':
            if (arg[2] == NUL) {
                new_landscape = TRUE;
                break;
            }


            if (sscanf(&arg[2], "%d", &lines) != 1
                || lines < 0 || lines > MAX_LINES)
            {
                fprintf(stderr, "Wrong value for option -l: '%s'. Ignored\n",
                        &arg[2]);
                break;
            }
            new_linesrequest = lines;
            break;
        case 'm':
            new_linesrequest = MAN_LINES;
            numbering = FALSE;
            break;
        case 'n':
            if (arg[2] == NUL) {
                numbering = TRUE;
                break;
            }
            switch (arg[2]) {
                case 'B':
                    new_fontweight = NORMAL;
                    break;
                case 'd':
                    printdate = FALSE;
                    break;
#if defined(SYSV) || defined(BSD)
                case 'L':
                    login_id = FALSE;
                    break;
#endif
                case 'l':
                    new_landscape = FALSE;
                    break;
                case 'm':
                    new_linesrequest = 0;
                    break;
                case 'n':
                    numbering = FALSE;
                    break;
                case 'p':
                    new_landscape = TRUE;
                    break;
                case 's':
                    no_border = TRUE;
                    break;
                case 'u':
                    filename_footer = FALSE;
                    break;
                default:
                    usage(EXIT_FAILURE);
            }
            break;
        case 'p':
            if (arg[2] != NUL)
                usage(EXIT_FAILURE);
            new_landscape = FALSE;
            break;
        case 's':
            if (arg[2] != NUL)
                usage(EXIT_FAILURE);
            no_border = FALSE;
            break;
        default:
            usage(EXIT_FAILURE);
    }
}
