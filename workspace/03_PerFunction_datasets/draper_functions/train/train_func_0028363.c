CmdGeometry(int code)
{
    char *options;
    options = getBraceParam();
    if (options) {
        diagnostics(2, "geometry command, argument %s\n", options);
        ParseOptGeometry(options);
        free(options);
    }
}
