main(int    argc,
     char **argv)
{
char           *filein, *printer;
char            buffer[512];
l_int32         ignore;
static char     mainName[] = "printtiff";

    if (argc != 2 && argc != 3)
	exit(ERROR_INT(" Syntax:  printtiff filein [printer]", mainName, 1));

    filein = argv[1];
    if (argc == 3)
	printer = argv[2];

    sprintf(buffer, "rm -f %s", TEMP_PS);
    ignore = system(buffer);

    convertTiffMultipageToPS(filein, TEMP_PS, NULL, FILL_FACTOR);

    if (argc == 3) {
	sprintf(buffer, "lpr -P%s %s &", printer, TEMP_PS);
	ignore = system(buffer);
    }

    return 0;
}
