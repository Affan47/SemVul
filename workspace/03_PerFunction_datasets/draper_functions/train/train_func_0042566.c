main(int    argc,
     char **argv)
{
char      *pagedir, *pagestr, *maskdir, *maskstr, *fileout;
l_int32    threshold, numpre, numpost, maxnum;
l_float32  textscale, imagescale;

    if (argc != 12) {
	fprintf(stderr,
            " Syntax: convertsegfilestops pagedir pagestr maskdir maskstr \\ \n"
            "                             numpre numpost maxnum \\ \n"
            "                             textscale imagescale thresh fileout\n"
            "     where\n"
            "         pagedir:  Input directory for page image files\n"
            "         pagestr:  Substring for matching; use 'allfiles' to\n"
            "                   convert all files in the page directory\n"
            "         maskdir:  Input directory for mask image files\n"
            "         maskstr:  Substring for matching; use 'allfiles' to\n"
            "                   convert all files in the mask directory\n"
            "         numpre:  Number of characters in name before number\n"
            "         numpost:  Number of characters in name after number\n"
            "         maxnum:  Only consider page numbers up to this value\n"
            "         textscale:  Scale of text output relative to pixs\n"
            "         imagescale:  Scale of image output relative to pixs\n"
            "         thresh:  threshold for binarization; typically about\n"
            "                  180; use 0 for default\n"
            "         fileout:  Output p file\n");
        return 1;
    }

    pagedir = argv[1];
    pagestr = argv[2];
    maskdir = argv[3];
    maskstr = argv[4];
    numpre = atoi(argv[5]);
    numpost = atoi(argv[6]);
    maxnum = atoi(argv[7]);
    textscale = atof(argv[8]);
    imagescale = atof(argv[9]);
    threshold = atoi(argv[10]);
    fileout = argv[11];

    if (!strcmp(pagestr, "allfiles"))
        pagestr = NULL;
    if (!strcmp(maskstr, "allfiles"))
        maskstr = NULL;

    return convertSegmentedPagesToPS(pagedir, pagestr, maskdir, maskstr,
                                     numpre, numpost, maxnum, textscale,
                                     imagescale, threshold, fileout);
}
