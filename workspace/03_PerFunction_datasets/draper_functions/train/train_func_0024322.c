main(int    argc,
         char **argv)
{
char        *filein, *fileout;
char         error_msg[] = " ps level = {1,2,3}; level 2 is default";
l_int32      level;
static char  mainName[] = "converttops";

    if (argc != 3 && argc != 4) {
        fprintf(stderr, "Syntax: converttops filein fileout [level]\n");
        fprintf(stderr, "%s\n", error_msg);
        return 1;
    }

    filein = argv[1];
    fileout = argv[2];

    level = 2;
    if (argc == 4) {
        level = atoi(argv[3]);
        if (level != 1 && level != 2 && level != 3) {
            L_WARNING("ps level must be 1, 2 or 3; setting to 2\n", mainName);
            level = 2;
        }
    }

    convertToPSEmbed(filein, fileout, level);
    return 0;
}
