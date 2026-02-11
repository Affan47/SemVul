main(int argc, char* argv[]) {
    char filename[300];
    const char *srcDir=NULL, *destDir=NULL, *suffix=NULL;
    char *basename=NULL;
    UErrorCode errorCode=U_ZERO_ERROR;

    U_MAIN_INIT_ARGS(argc, argv);


    options[DESTDIR].value=u_getDataDirectory();
    options[SOURCEDIR].value="";
    options[UNICODE_VERSION].value="";
    options[ICUDATADIR].value=u_getDataDirectory();
    argc=u_parseArgs(argc, argv, sizeof(options)/sizeof(options[0]), options);


    if(argc<0) {
        fprintf(stderr,
            "error in command line argument \"%s\"\n",
            argv[-argc]);
    }
    if(argc<0 || options[HELP_H].doesOccur || options[HELP_QUESTION_MARK].doesOccur) {


        fprintf(stderr,
            "Usage: %s [-options] [suffix]\n"
            "\n"
            "read the UnicodeData.txt file and other Unicode properties files and\n"
            "create a binary file " DATA_NAME "." DATA_TYPE " with the character properties\n"
            "\n",
            argv[0]);
        fprintf(stderr,
            "Options:\n"
            "\t-h or -? or --help  this usage text\n"
            "\t-v or --verbose     verbose output\n"
            "\t-c or --copyright   include a copyright notice\n"
            "\t-u or --unicode     Unicode version, followed by the version like 3.0.0\n"
            "\t-C or --csource     generate a .c source file rather than the .icu binary\n");
        fprintf(stderr,
            "\t-d or --destdir     destination directory, followed by the path\n"
            "\t-s or --sourcedir   source directory, followed by the path\n"
            "\t-i or --icudatadir  directory for locating any needed intermediate data files,\n"
            "\t                    followed by path, defaults to %s\n"
            "\tsuffix              suffix that is to be appended with a '-'\n"
            "\t                    to the source file basenames before opening;\n"
            "\t                    'genprops new' will read UnicodeData-new.txt etc.\n",
            u_getDataDirectory());
        return argc<0 ? U_ILLEGAL_ARGUMENT_ERROR : U_ZERO_ERROR;
    }


    beVerbose=options[VERBOSE].doesOccur;
    haveCopyright=options[COPYRIGHT].doesOccur;
    srcDir=options[SOURCEDIR].value;
    destDir=options[DESTDIR].value;

    if(argc>=2) {
        suffix=argv[1];
    } else {
        suffix=NULL;
    }

    if(options[UNICODE_VERSION].doesOccur) {
        setUnicodeVersion(options[UNICODE_VERSION].value);
    }


    if (options[ICUDATADIR].doesOccur) {
        u_setDataDirectory(options[ICUDATADIR].value);
    }


    uprv_strcpy(filename, srcDir);
    basename=filename+uprv_strlen(filename);
    if(basename>filename && *(basename-1)!=U_FILE_SEP_CHAR) {
        *basename++=U_FILE_SEP_CHAR;
    }


    initStore();


    writeUCDFilename(basename, "UnicodeData", suffix);
    parseDB(filename, &errorCode);


    *basename=0;
    generateAdditionalProperties(filename, suffix, &errorCode);


    if(U_SUCCESS(errorCode)) {

        generateData(destDir, options[CSOURCE].doesOccur);
    }

    exitStore();
    u_cleanup();
    return errorCode;
}
