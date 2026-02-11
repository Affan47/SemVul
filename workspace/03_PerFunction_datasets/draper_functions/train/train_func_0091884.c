dump_unget(
    const char *    why
)


{
    const FILEINFO *    file;

    mcpp_fputs( "dump of pending input text", DBG);
    if (why != NULL) {
        mcpp_fputs( "-- ", DBG);
        mcpp_fputs( why, DBG);
    }
    mcpp_fputc( '\n', DBG);

    for (file = infile; file != NULL; file = file->parent)
        dump_string( file->real_fname ? file->real_fname
                : file->filename ? file->filename : "NULL", file->bptr);
}
