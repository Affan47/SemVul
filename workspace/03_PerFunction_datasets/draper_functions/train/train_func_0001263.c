d_message(const int level, const char* ifmt, const char *msg)
{
    char*  fmt;
    if (debug < level) return;
    fprintf(stderr,"DEBUG: ");
    fmt = (char *)ifmt;
    if (!fmt)
        fmt = (char *)"%s\n";
    fprintf(stderr, fmt, msg);
    fflush(stderr);
}
