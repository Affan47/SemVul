open_files(FilePair *files)
{
    if(!strncmp(files->infile, "-", 2)) {
#ifdef _WIN32
        _setmode(_fileno(stdin), _O_BINARY);
#endif
        files->ifp = stdin;
    } else {
        files->ifp = fopen(files->infile, "rb");
        if(!files->ifp) {
            fprintf(stderr, "error opening input file: %s\n", files->infile);
            return 1;
        }
    }
    if(!strncmp(files->outfile, "-", 2)) {
#ifdef _WIN32
        _setmode(_fileno(stdout), _O_BINARY);
#endif
        files->ofp = stdout;
    } else {
        files->ofp = fopen(files->outfile, "wb");
        if(!files->ofp) {
            fprintf(stderr, "error opening output file: %s\n", files->outfile);
            return 1;
        }
    }
    return 0;
}
