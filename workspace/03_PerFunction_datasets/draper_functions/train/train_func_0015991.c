count_lines( const char *s )
{
    int count;

    if ( ! s )
        return 0;

    for ( count = 1; *s; s++ )
        if ( *s == '\n' )
            count++;

    return count;
}
