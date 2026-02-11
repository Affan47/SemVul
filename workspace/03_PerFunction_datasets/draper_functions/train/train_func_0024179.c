copyArgv(int argc, char *argv[])
{
    int i;
    char **new_argv;

    new_argv = stgCallocBytes(argc + 1, sizeof (char *), "copyArgv 1");
    for (i = 0; i < argc; i++) {
        new_argv[i] = copyArg(argv[i]);
    }
    new_argv[argc] = NULL;
    return new_argv;
}
