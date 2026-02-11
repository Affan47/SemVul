ext_keytab_wrap(int argc, char **argv)
{
    struct ext_keytab_options opt;
    int ret;
    int optidx = 0;
    struct getargs args[] = {
        { "keytab", 'k', arg_string, NULL, "keytab to use", NULL },
        { "help", 'h', arg_flag, NULL, NULL, NULL }
    };
    int help_flag = 0;
    opt.keytab_string = NULL;
    args[0].value = &opt.keytab_string;
    args[1].value = &help_flag;
    if(getarg(args, 2, argc, argv, &optidx))
        goto usage;
    if(argc - optidx < 1) {
        fprintf(stderr, "Arguments given (%u) are less than expected (1).\n\n", argc - optidx);
        goto usage;
    }
    if(help_flag)
        goto usage;
    ret = ext_keytab(&opt, argc - optidx, argv + optidx);
    return ret;
usage:
    arg_printusage (args, 2, "ext_keytab", "principal...");
    return 0;
}
