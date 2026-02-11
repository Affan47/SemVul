add_wrap(int argc, char **argv)
{
    struct add_options opt;
    int ret;
    int optidx = 0;
    struct getargs args[] = {
        { "principal", 'p', arg_string, NULL, "principal to add", "principal" },
        { "kvno", 'V', arg_integer, NULL, "key version number", NULL },
        { "enctype", 'e', arg_string, NULL, "encryption type", "enctype" },
        { "password", 'w', arg_string, NULL, "password for key", NULL },
        { "salt", 's', arg_negative_flag, NULL, "use unsalted keys", NULL },
        { "random", 'r', arg_flag, NULL, "generate random key", NULL },
        { "hex", 'H', arg_flag, NULL, "password is a hexadecimal string", NULL },
        { "help", 'h', arg_flag, NULL, NULL, NULL }
    };
    int help_flag = 0;
    opt.principal_string = (char *)(unsigned long)"";
    opt.kvno_integer = -1;
    opt.enctype_string = NULL;
    opt.password_string = NULL;
    opt.salt_flag = 1;
    opt.random_flag = 0;
    opt.hex_flag = 0;
    args[0].value = &opt.principal_string;
    args[1].value = &opt.kvno_integer;
    args[2].value = &opt.enctype_string;
    args[3].value = &opt.password_string;
    args[4].value = &opt.salt_flag;
    args[5].value = &opt.random_flag;
    args[6].value = &opt.hex_flag;
    args[7].value = &help_flag;
    if(getarg(args, 8, argc, argv, &optidx))
        goto usage;
    if(argc - optidx > 0) {
        fprintf(stderr, "Arguments given (%u) are more than expected (0).\n\n", argc - optidx);
        goto usage;
    }
    if(help_flag)
        goto usage;
    ret = kt_add(&opt, argc - optidx, argv + optidx);
    return ret;
usage:
    arg_printusage (args, 8, "add", "");
    return 0;
}
