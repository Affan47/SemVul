debug_newvstralloc(
    const char *file,
    int		line,
    char *	oldstr,
    const char *newstr,
    ...)
{
    va_list argp;
    char *result;

    arglist_start(argp, newstr);
    result = internal_vstralloc(file, line, newstr, argp);
    arglist_end(argp);
    amfree(oldstr);
    return result;
}
