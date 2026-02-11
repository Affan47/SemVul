x264_atobool( const char *str, int *b_error )
{
    if( !strcmp(str, "1") ||
        !strcmp(str, "true") ||
        !strcmp(str, "yes") )
        return 1;
    if( !strcmp(str, "0") ||
        !strcmp(str, "false") ||
        !strcmp(str, "no") )
        return 0;
    *b_error = 1;
    return 0;
}
