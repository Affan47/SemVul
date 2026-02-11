main(int    argc,
         char **argv)
{
char        *filename;
l_int32      index, ret;
SELA        *sela;
static char  mainName[] = "fcombautogen";

    if (argc != 2 && argc != 3)
        return ERROR_INT(" Syntax:  fcombautogen index <filename>",
                         mainName, 1);

    index = atoi(argv[1]);
    sela = selaAddDwaCombs(NULL);

    if (argc == 2)
        filename = stringNew("dwacomb");
    else
        filename = argv[2];
    ret = fmorphautogen(sela, index, filename);

    if (argc == 2)
        lept_free(filename);
    selaDestroy(&sela);
    return ret;
}
