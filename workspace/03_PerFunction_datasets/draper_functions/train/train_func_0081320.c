Ns_DStringAppendArgv(Ns_DString *dsPtr)
{
    char *s, **argv;
    int i, argc, len, size;


    argc = 0;
    s = dsPtr->string;
    while (*s != '\0') {
	++argc;
	s += strlen(s) + 1;
    }


    len = ((dsPtr->length / 8) + 1) * 8;
    size = len + (sizeof(char *) * (argc + 1));
    Ns_DStringSetLength(dsPtr, size);


    s = dsPtr->string;
    argv = (char **) (s + len);
    for (i = 0; i < argc; ++i) {
	argv[i] = s;
	s += strlen(s) + 1;
    }
    argv[i] = NULL;
    return argv;
}
