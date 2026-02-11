dump_wrap(int argc, char **argv)
{
    struct dump_options opt;
    int ret;
    int optidx = 0;
    struct getargs args[] = {
        { "decrypt", 'd', arg_flag, NULL, "decrypt keys", NULL },
        { "format", 'f', arg_string, NULL, "dump format, mit or heimdal (default: heimdal)", NULL },
        { "help", 'h', arg_flag, NULL, NULL, NULL }
    };
    int help_flag = 0;
    opt.decrypt_flag = 0;
    opt.format_string = NULL;
    args[0].value = &opt.decrypt_flag;
    args[1].value = &opt.format_string;
    args[2].value = &help_flag;
    if(getarg(args, 3, argc, argv, &optidx))
        goto usage;
    if(argc - optidx > 1) {
        fprintf(stderr, "Arguments given (%u) are more than expected (1).\n\n", argc - optidx);
        goto usage;
    }
    if(argc - optidx < 0) {
        fprintf(stderr, "Arguments given (%u) are less than expected (0).\n\n", argc - optidx);
        goto usage;
    }
    if(help_flag)
        goto usage;
    ret = dump(&opt, argc - optidx, argv + optidx);
    return ret;
usage:
    arg_printusage (args, 3, "dump", "[dump-file]");
    return 0;
}
