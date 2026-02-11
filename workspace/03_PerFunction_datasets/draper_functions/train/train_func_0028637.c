main(int    argc,
     char **argv)
{
char        *dirin, *substr, *title, *fileout;
l_int32      ret, res, type;
l_float32    scalefactor;
static char  mainName[] = "convertfilestopdf";

    if (argc != 8) {
        fprintf(stderr,
            " Syntax: convertfilestopdf dirin substr res"
            " scalefactor encoding_type, title fileout\n"
            "         dirin:  input directory for image files\n"
            "         substr:  Use 'allfiles' to convert all files\n"
            "                  in the directory.\n"
            "         res:  Input resolution of each image;\n"
            "               assumed to all be the same\n"
            "         scalefactor:  Use to scale all images\n"
            "         encoding_type:\n"
            "              L_JPEG_ENCODE = 1\n"
            "              L_G4_ENCODE = 2\n"
            "              L_FLATE_ENCODE = 3, or 0 for per-page default)\n"
            "         title:  Use 'none' to omit\n"
            "         fileout:  Output pdf file\n");
        return 1;
    }

    dirin = argv[1];
    substr = argv[2];
    res = atoi(argv[3]);
    scalefactor = atof(argv[4]);
    type = atoi(argv[5]);
    title = argv[6];
    fileout = argv[7];
    if (!strcmp(substr, "allfiles"))
        substr = NULL;
    if (scalefactor <= 0.0 || scalefactor > 1.0) {
        L_WARNING("invalid scalefactor: setting to 1.0", mainName);
        scalefactor = 1.0;
    }
    if (!strcmp(title, "none"))
        title = NULL;

    ret = convertFilesToPdf(dirin, substr, res, scalefactor, type,
                            75, title, fileout);
    return ret;
}
