gRecvStrArr(int *rnum)
{
    int num;
    char **argv, **cargv;

    gDebug("receiving string array from %s ...\n", curtalk->pipe->who);
    gRead(&num, sizeof(num));
    gDebug(" -> %d strings\n", num);
    *rnum = num;
    if (!num)
        return 0;
    if (!(argv = Malloc(num * sizeof(char *))))
        gErr();
    for (cargv = argv; --num >= 0; cargv++)
        *cargv = gRecvStr();
    return argv;
}
