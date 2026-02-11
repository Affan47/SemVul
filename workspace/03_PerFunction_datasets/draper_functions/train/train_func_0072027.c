input_init(input_parameter *param, int id)
{
    int i;
    plugin_number = id;

    param->argv[0] = INPUT_PLUGIN_NAME;


    for(i = 0; i < param->argc; i++) {
        DBG("argv[%d]=%s\n", i, param->argv[i]);
    }

    reset_getopt();
    while(1) {
        int option_index = 0, c = 0;
        static struct option long_options[] = {
            {"h", no_argument, 0, 0
            },
            {"help", no_argument, 0, 0},
            {"d", required_argument, 0, 0},
            {"delay", required_argument, 0, 0},
            {"f", required_argument, 0, 0},
            {"folder", required_argument, 0, 0},
            {"r", no_argument, 0, 0},
            {"remove", no_argument, 0, 0},
            {"n", required_argument, 0, 0},
            {"name", required_argument, 0, 0},
            {0, 0, 0, 0}
        };

        c = getopt_long_only(param->argc, param->argv, "", long_options, &option_index);


        if(c == -1) break;


        if(c == '?') {
            help();
            return 1;
        }

        switch(option_index) {

        case 0:
        case 1:
            DBG("case 0,1\n");
            help();
            return 1;
            break;


        case 2:
        case 3:
            DBG("case 2,3\n");
            delay = atoi(optarg);
            break;


        case 4:
        case 5:
            DBG("case 4,5\n");
            folder = malloc(strlen(optarg) + 2);
            strcpy(folder, optarg);
            if(optarg[strlen(optarg)-1] != '/')
                strcat(folder, "/");
            break;


        case 6:
        case 7:
            DBG("case 6,7\n");
            rm = 1;
            break;


        case 8:
        case 9:
            DBG("case 8,9\n");
            filename = malloc(strlen(optarg) + 2);
            strcpy(filename, optarg);
            break;

        default:
            DBG("default case\n");
            help();
            return 1;
        }
    }

    pglobal = param->global;


    if(folder == NULL) {
        IPRINT("ERROR: no folder specified\n");
        return 1;
    }

    IPRINT("folder to watch...: %s\n", folder);
    IPRINT("forced delay......: %i\n", delay);
    IPRINT("delete file.......: %s\n", (rm) ? "yes, delete" : "no, do not delete");
    IPRINT("filename must be..: %s\n", (filename == NULL) ? "-no filter for certain filename set-" : filename);

    return 0;
}
