parse_args(int argc, char *argv[])
{
    int arg;

    if (argc > 5) {
        show_usage(argv[0]);
        ::exit(-1);
    }

    while ((arg = getopt(argc, argv, "l:i:hv")) != -1) {
        switch (arg) {
            case 'l':
                logfile = optarg;
                break;
            case 'h':
                show_usage(argv[0]);
                ::exit(0);
            case 'v':

                qWarning("amora-applet (unspecified version)");
                ::exit(0);
            case 'i':
                bt_hci = atoi(optarg);
                break;
            default:
                show_usage(argv[0]);
                ::exit(0);
        }
    }
}
